// pass9_3_declare_load_fns.cpp
#include "pass9_3_declare_load_fns.hpp"

#include <cassert>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include <llvm/IR/Module.h>

namespace sema
{
    static void push_diag(std::vector<Pass9_3Diagnostic>& ds,
                          Pass9_3Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        ds.push_back(Pass9_3Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    static std::string sanitize_symbol(std::string_view s)
    {
        std::string out;
        out.reserve(s.size());
        for (char c : s)
        {
            const bool ok =
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c >= '0' && c <= '9') ||
                c == '_';
            out.push_back(ok ? c : '_');
        }
        if (out.empty()) out = "_";
        return out;
    }

    static std::string sanitize_key(const std::string& k)
    {
        return sanitize_symbol(std::string_view{k});
    }

    static std::string mangle_fn_name(const Pass2Result& p2,
                                      ModuleId mid,
                                      lex::SymId fn_name,
                                      CompilerContext& ctx)
    {
        std::string mod_key = "unknown";
        if (mid.value < p2.modules.size())
            mod_key = p2.modules[mid.value].key;

        std::string_view fn_sv = ctx.identInterner.view(fn_name);

        std::ostringstream oss;
        oss << "fn__m_" << sanitize_key(mod_key) << "__" << sanitize_symbol(fn_sv);
        return oss.str();
    }

    // Resolve "the" entry function by public name. Must be unique across all modules.
    // On duplicates/missing, emits diagnostics and returns nullopt.
    static std::optional<FnId> resolve_entry_fn(Pass9_3Result& out,
                                               const Pass4Result& p4,
                                               lex::SymId entrypoint_name)
    {
        std::optional<FnId> found;
        bool dup = false;

        for (const auto& mg : p4.modules)
        {
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
                    push_diag(out.diagnostics,
                              Pass9_3Diagnostic::Code::DuplicateEntrypoint,
                              fs.loc,
                              "multiple public entrypoint functions with the same name");
                }
            }
        }

        if (dup)
            return std::nullopt;

        if (!found.has_value())
        {
            push_diag(out.diagnostics,
                      Pass9_3Diagnostic::Code::MissingEntrypoint,
                      lex::Loc{},
                      "no public entrypoint function found");
        }

        return found;
    }

    static llvm::Type* llvm_abi_type_for(TypeId tid,
                                         const Pass5Result& p5,
                                         const Pass9_1Result& st)
    {
        if (tid.value >= p5.types.nodes.size())
            return st.obj_ptr_ty;

        const TypeNode& n = p5.types.nodes[tid.value];

        // Dynamic ABI rule:
        //   - void => void
        //   - bool => i1
        //   - everything else => Obj*
        if (n.kind == TypeKind::Builtin)
        {
            if (n.builtin == BuiltinType::Void) return st.void_ty;
            if (n.builtin == BuiltinType::Bool) return st.i1_ty;
            return st.obj_ptr_ty;
        }

        return st.obj_ptr_ty;
    }

    static llvm::Function* get_or_declare_checked(llvm::Module& M,
                                                  llvm::FunctionType* FT,
                                                  llvm::StringRef name,
                                                  bool& type_mismatch)
    {
        type_mismatch = false;

        if (auto* F = M.getFunction(name))
        {
            if (F->getFunctionType() != FT)
                type_mismatch = true;
            return F;
        }

        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

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
        // If missing/duplicate, we still declare all functions, but entry won't be special-cased.
        const std::optional<FnId> entry_fnid = resolve_entry_fn(out, p4, entrypoint);

        const auto n_units = static_cast<std::uint32_t>(p4.modules.size());

        for (std::uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            const ModuleGlobals& mg = p4.modules[unit_i];
            const ModuleId mid = mg.module_id;

            // ---- user functions ----
            for (const FnSym& fs : mg.fns)
            {
                if (!fs.decl)
                    continue;

                // Default: mangled symbol.
                std::string ir_name = mangle_fn_name(p2, mid, fs.name, ctx);

                // If this is the resolved entry function, give it the stable public IR name.
                // Typically `entrypoint` is interned "main", so this becomes "@main".
                if (entry_fnid.has_value() && fs.id == *entry_fnid)
                    ir_name = std::string(ctx.identInterner.view(entrypoint));

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
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{0};

                    llvm::Type* PT = llvm_abi_type_for(tid, p5, st);
                    if (PT == st.void_ty) PT = st.obj_ptr_ty; // no void params
                    params.push_back(PT);
                }

                llvm::Type* ret_ty = st.void_ty;
                if (fs.decl->ret_)
                {
                    auto it = p5.type_of.find(fs.decl->ret_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{0};
                    ret_ty = llvm_abi_type_for(tid, p5, st);
                }

                auto* FT = llvm::FunctionType::get(ret_ty, params, false);

                bool mismatch = false;
                llvm::Function* F = get_or_declare_checked(M, FT, ir_name, mismatch);

                if (mismatch)
                {
                    std::ostringstream oss;
                    oss << "LLVM function already exists with different type: " << ir_name;
                    push_diag(out.diagnostics,
                              Pass9_3Diagnostic::Code::LlvmFunctionTypeMismatch,
                              fs.loc,
                              oss.str());
                    continue;
                }

                // Entry must be externally visible (even if you later add other linkage rules).
                const bool is_entry = (entry_fnid.has_value() && fs.id == *entry_fnid);

                if (!fs.is_public && !is_entry)
                    F->setLinkage(llvm::GlobalValue::InternalLinkage);
                else
                    F->setLinkage(llvm::GlobalValue::ExternalLinkage);

                st.fn_decls.emplace(fs.id, F);
            }

            // ---- load functions (declaration-only, no bodies) ----
            for (const LoadFnSym& ls : mg.load_fns)
            {
                if (!ls.decl)
                    continue;

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
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{0};

                    llvm::Type* PT = llvm_abi_type_for(tid, p5, st);
                    if (PT == st.void_ty) PT = st.obj_ptr_ty;
                    params.push_back(PT);
                }

                llvm::Type* ret_ty = st.void_ty;
                if (ls.decl->ret_)
                {
                    auto it = p5.type_of.find(ls.decl->ret_);
                    TypeId tid = (it != p5.type_of.end()) ? it->second : TypeId{0};
                    ret_ty = llvm_abi_type_for(tid, p5, st);
                }

                auto* FT = llvm::FunctionType::get(ret_ty, params, false);

                bool mismatch = false;
                llvm::Function* F =
                    get_or_declare_checked(M, FT, ctx.identInterner.view(ls.name), mismatch);

                if (mismatch)
                {
                    std::ostringstream oss;
                    oss << "LLVM load-fn already exists with different type: "
                        << ctx.identInterner.view(ls.name);
                    push_diag(out.diagnostics,
                              Pass9_3Diagnostic::Code::LlvmFunctionTypeMismatch,
                              ls.loc,
                              oss.str());
                    continue;
                }

                // load fns should usually be ExternalLinkage (JIT provides them)
                F->setLinkage(llvm::GlobalValue::ExternalLinkage);

                st.load_fn_decls.emplace(ls.id, F);
            }
        }

        return out;
    }
} // namespace sema
