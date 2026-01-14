// sema/pass9_3.cpp
#include "pass9_3_declare_load_fns.hpp"

#include <cassert>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <llvm/ADT/StringRef.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

// Needed for module-path-first logging:
#include "module/module.hpp"
#include "compiler_context.hpp"

namespace sema
{
    // ------------------------------------------------------------
    // Logging helpers (REQUIREMENT: each cluster begins with module path LogPath)
    // ------------------------------------------------------------

    static const ast::Module* unit_mod_or_fallback(const Pass9_1Result& st, std::uint32_t unit_i)
    {
        if (unit_i < st.unit_mods.size() && st.unit_mods[unit_i])
            return st.unit_mods[unit_i];
        return st.log_mod;
    }

    static void push_log(LogSequence& logs,
                         const ast::Module* mod,
                         const lex::Loc& loc,
                         std::string msg)
    {
        // Cluster begins with module path.
        if (mod && mod->pathExpr_)
            logs.emplace_back(LogPath{ SymKind::Ident, mod->pathExpr_->path_, loc });
        else
            logs.emplace_back(LogPath{ SymKind::Ident, {}, loc });

        logs.emplace_back(std::move(msg));
    }

    static void push_log_ident(LogSequence& logs,
                               const ast::Module* mod,
                               const lex::Loc& loc,
                               std::string msg,
                               lex::SymId name)
    {
        push_log(logs, mod, loc, std::move(msg));
        logs.emplace_back(Log{ SymKind::Ident, name, loc });
    }

    // ------------------------------------------------------------
    // LLVM helpers
    // ------------------------------------------------------------

    static bool same_fty(const llvm::FunctionType* a, const llvm::FunctionType* b)
    {
        if (a == b) return true;
        if (!a || !b) return false;

        if (a->getReturnType() != b->getReturnType()) return false;
        if (a->isVarArg() != b->isVarArg()) return false;
        if (a->getNumParams() != b->getNumParams()) return false;

        for (unsigned i = 0; i < a->getNumParams(); ++i)
            if (a->getParamType(i) != b->getParamType(i))
                return false;

        return true;
    }

    static llvm::Function* get_or_declare_checked(llvm::Module& M,
                                                 llvm::FunctionType* FT,
                                                 llvm::StringRef name,
                                                 bool& type_mismatch)
    {
        type_mismatch = false;

        if (auto* F = M.getFunction(name))
        {
            if (!same_fty(F->getFunctionType(), FT))
                type_mismatch = true;
            return F;
        }

        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

    // ------------------------------------------------------------
    // Name mangling / sanitization
    // ------------------------------------------------------------

    static std::string sanitize_symbol(std::string_view s)
    {
        std::string out;
        out.reserve(s.size());
        for (char c : s)
        {
            const bool ok = (c >= 'a' && c <= 'z') ||
                            (c >= 'A' && c <= 'Z') ||
                            (c >= '0' && c <= '9') ||
                            (c == '_');
            out.push_back(ok ? c : '_');
        }
        if (out.empty()) out = "_";
        return out;
    }

    static std::string sanitize_key(const std::string& k)
    {
        return sanitize_symbol(std::string_view{k});
    }

    static std::string mangle_user_fn_name(const Pass2Result& p2,
                                           ModuleId mid,
                                           lex::SymId fn_name,
                                           CompilerContext& ctx)
    {
        std::string mod_key = "unknown";
        if (mid.value < p2.modules.size())
            mod_key = p2.modules[mid.value].key;

        const std::string_view fn_sv = ctx.identInterner.view(fn_name);

        std::ostringstream oss;
        oss << "fn__m_" << sanitize_key(mod_key) << "__" << sanitize_symbol(fn_sv);
        return oss.str();
    }

    // ------------------------------------------------------------
    // Entrypoint resolution (public name, unique across modules)
    // ------------------------------------------------------------

    static std::optional<FnId> resolve_entry_fn(Pass9_3Result& out,
                                               const Pass9_1Result& st,
                                               const Pass4Result& p4,
                                               lex::SymId entrypoint_name)
    {
        std::optional<FnId> found;
        bool dup = false;

        const auto n_units = static_cast<std::uint32_t>(p4.modules.size());

        for (std::uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            const ModuleGlobals& mg = p4.modules[unit_i];

            for (const FnSym& fs : mg.fns)
            {
                if (!fs.decl) continue;
                if (!fs.is_public) continue;
                if (fs.name != entrypoint_name) continue;

                if (!found.has_value())
                {
                    found = fs.id;
                }
                else
                {
                    dup = true;
                    push_log(out.errors,
                             unit_mod_or_fallback(st, unit_i),
                             fs.loc,
                             "pass9.3: DuplicateEntrypoint: multiple public entrypoint functions with the same name");
                }
            }
        }

        if (dup)
            return std::nullopt;

        if (!found.has_value())
        {
            push_log(out.errors,
                     st.log_mod,
                     lex::Loc{},
                     "pass9.3: MissingEntrypoint: no public entrypoint function found");
        }

        return found;
    }

    // ------------------------------------------------------------
    // ABI typing (dynamic ABI rule)
    // ------------------------------------------------------------

    static llvm::Type* llvm_abi_type_for(TypeId tid,
                                         const Pass5Result& p5,
                                         const Pass9_1Result& st)
    {
        if (tid.value >= p5.types.nodes.size())
            return st.obj_ptr_ty;

        const TypeNode& n = p5.types.nodes[tid.value];

        // Dynamic ABI rule:
        //  - void => void
        //  - bool => i1
        //  - everything else => Obj*
        if (n.kind == TypeKind::Builtin)
        {
            if (n.builtin == BuiltinType::Void) return st.void_ty;
            if (n.builtin == BuiltinType::Bool) return st.i1_ty;
            return st.obj_ptr_ty;
        }

        return st.obj_ptr_ty;
    }

    // ------------------------------------------------------------
    // For user fns: guarantee a unique IR symbol per FnId
    // ------------------------------------------------------------

    static std::string disambiguate_user_symbol(Pass9_3Result& out,
                                                const Pass9_1Result& st,
                                                std::uint32_t unit_i,
                                                llvm::Module& M,
                                                std::unordered_map<std::string, FnId>& owner,
                                                const std::string& base,
                                                const FnSym& fs)
    {
        auto taken_by_this_pass = [&](const std::string& nm) -> bool
        {
            auto it = owner.find(nm);
            return (it != owner.end() && it->second != fs.id);
        };

        auto exists_in_module = [&](const std::string& nm) -> bool
        {
            return M.getFunction(nm) != nullptr;
        };

        if (!taken_by_this_pass(base) && !exists_in_module(base))
        {
            owner.emplace(base, fs.id);
            return base;
        }

        {
            std::ostringstream oss;
            oss << "pass9.3: DuplicateLlvmFunctionName: duplicate LLVM function symbol name: " << base;
            push_log(out.errors,
                     unit_mod_or_fallback(st, unit_i),
                     fs.loc,
                     oss.str());
        }

        // Deterministic suffix so rebuilds are stable.
        std::ostringstream nm;
        nm << base << "__dup_fn_" << fs.id.index;

        std::string cand = nm.str();
        unsigned ctr = 0;
        while (taken_by_this_pass(cand) || exists_in_module(cand))
        {
            std::ostringstream nm2;
            nm2 << base << "__dup_fn_" << fs.id.index << "_" << ctr++;
            cand = nm2.str();
        }

        owner.emplace(cand, fs.id);
        return cand;
    }

    // ------------------------------------------------------------
    // Driver
    // ------------------------------------------------------------

    Pass9_3Result run_pass9_3_declare_user_and_load_fns(Pass9_1Result& st,
                                                        const Pass2Result& p2,
                                                        const Pass4Result& p4,
                                                        const Pass5Result& p5,
                                                        CompilerContext& ctx,
                                                        lex::SymId entrypoint)
    {
        assert(st.module && st.llctx);

        Pass9_3Result out{};
        llvm::Module& M = *st.module;

        // Pass9.3 is the only place that fills these maps.
        st.fn_decls.clear();
        st.load_fn_decls.clear();

        // Resolve unique entry function (public, named `entrypoint`).
        const std::optional<FnId> entry_fnid = resolve_entry_fn(out, st, p4, entrypoint);

        // Track user-fn symbols to avoid accidental aliasing between FnIds.
        std::unordered_map<std::string, FnId> user_symbol_owner;

        const auto n_units = static_cast<std::uint32_t>(p4.modules.size());

        for (std::uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            const ModuleGlobals& mg = p4.modules[unit_i];
            const ModuleId mid = mg.module_id;

            // ---- user functions ----
            for (const FnSym& fs : mg.fns)
            {
                if (!fs.decl) continue;

                // Default: mangled symbol.
                std::string ir_name = mangle_user_fn_name(p2, mid, fs.name, ctx);

                // If resolved entry function, prefer stable public IR name (e.g. "@main").
                if (entry_fnid.has_value() && fs.id == *entry_fnid)
                    ir_name = std::string(ctx.identInterner.view(entrypoint));

                // Guarantee a unique name for this FnId (avoid FnId->same llvm::Function* aliasing).
                ir_name = disambiguate_user_symbol(out, st, unit_i, M, user_symbol_owner, ir_name, fs);

                // Build ABI param list
                std::vector<llvm::Type*> params;
                params.reserve(fs.decl->params_.size());

                for (auto* p : fs.decl->params_)
                {
                    if (!p || !p->type_)
                    {
                        params.push_back(st.obj_ptr_ty);
                        continue;
                    }

                    auto it = p5.type_of.find(p->type_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{UINT32_MAX};

                    llvm::Type* PT = llvm_abi_type_for(tid, p5, st);
                    if (PT == st.void_ty) PT = st.obj_ptr_ty; // no void params
                    params.push_back(PT);
                }

                // Return type
                llvm::Type* ret_ty = st.void_ty;
                if (fs.decl->ret_)
                {
                    auto it = p5.type_of.find(fs.decl->ret_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{UINT32_MAX};
                    ret_ty = llvm_abi_type_for(tid, p5, st);
                }

                auto* FT = llvm::FunctionType::get(ret_ty, params, false);

                bool mismatch = false;
                llvm::Function* F = get_or_declare_checked(M, FT, ir_name, mismatch);

                if (mismatch)
                {
                    {
                        std::ostringstream oss;
                        oss << "pass9.3: LlvmFunctionTypeMismatch: LLVM function already exists with different type: " << ir_name;
                        push_log(out.errors,
                                 unit_mod_or_fallback(st, unit_i),
                                 fs.loc,
                                 oss.str());
                    }

                    // Declaring under the same name is unsafe.
                    // Create a deterministic disambiguated *new* name and declare the correct type.
                    std::ostringstream nm;
                    nm << ir_name << "__tyfix_fn_" << fs.id.index;

                    std::string fixed = nm.str();
                    unsigned ctr = 0;
                    while (M.getFunction(fixed))
                    {
                        std::ostringstream nm2;
                        nm2 << ir_name << "__tyfix_fn_" << fs.id.index << "_" << ctr++;
                        fixed = nm2.str();
                    }

                    F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, fixed, M);

                    // Track ownership to avoid later aliasing within this pass.
                    user_symbol_owner.emplace(fixed, fs.id);
                }

                // Entry must be externally visible.
                const bool is_entry = (entry_fnid.has_value() && fs.id == *entry_fnid);
                if (!fs.is_public && !is_entry)
                    F->setLinkage(llvm::GlobalValue::InternalLinkage);
                else
                    F->setLinkage(llvm::GlobalValue::ExternalLinkage);

                st.fn_decls.emplace(fs.id, F);
            }

            // ---- load functions (declaration-only, externals by declared name) ----
            for (const LoadFnSym& ls : mg.load_fns)
            {
                if (!ls.decl) continue;

                std::vector<llvm::Type*> params;
                params.reserve(ls.decl->params_.size());

                for (auto* p : ls.decl->params_)
                {
                    if (!p || !p->type_)
                    {
                        params.push_back(st.obj_ptr_ty);
                        continue;
                    }

                    auto it = p5.type_of.find(p->type_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{UINT32_MAX};

                    llvm::Type* PT = llvm_abi_type_for(tid, p5, st);
                    if (PT == st.void_ty) PT = st.obj_ptr_ty; // no void params
                    params.push_back(PT);
                }

                llvm::Type* ret_ty = st.void_ty;
                if (ls.decl->ret_)
                {
                    auto it = p5.type_of.find(ls.decl->ret_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{UINT32_MAX};
                    ret_ty = llvm_abi_type_for(tid, p5, st);
                }

                auto* FT = llvm::FunctionType::get(ret_ty, params, false);

                const llvm::StringRef ext_name = ctx.identInterner.view(ls.name);

                bool mismatch = false;
                llvm::Function* F = get_or_declare_checked(M, FT, ext_name, mismatch);

                // For load-fns, duplicates by name are allowed (same external symbol),
                // but type mismatch is a real error.
                if (mismatch)
                {
                    std::ostringstream oss;
                    oss << "pass9.3: LlvmFunctionTypeMismatch: LLVM load-fn symbol '"
                        << ext_name.str() << "' already exists with different type";
                    push_log(out.errors,
                             unit_mod_or_fallback(st, unit_i),
                             ls.loc,
                             oss.str());
                }

                F->setLinkage(llvm::GlobalValue::ExternalLinkage);
                st.load_fn_decls.emplace(ls.id, F);
            }
        }

        return out;
    }
} // namespace sema
