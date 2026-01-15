#ifndef INZ_SEMA_NAME_RESOLVE_PASS3_HPP
#define INZ_SEMA_NAME_RESOLVE_PASS3_HPP

#include <cstdint>
#include <vector>
#include <optional>
#include <variant>
#include <type_traits>

#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>

#include "sema/module_import_pass.hpp"  // Pass1: ModulePassDB, ModuleId, PathPool
#include "sema/scope_pass.hpp"         // Pass2: ScopePass2DB, ModuleScope, Symbol, binders
#include "hir/arena_holder.hpp"
#include "hir/arena.hpp"

namespace sema
{
    // --------------------------------------------
    // Pass 3 diagnostics (ONLY pass-3-level)
    // --------------------------------------------
    enum class NameRes3ErrKind : uint8_t
    {
        UnresolvedTypeName,
        UnresolvedValueName,
        NotAType,
        NotAValue,
        GenericArityMismatch,
        DuplicateLocalName
    };

    struct NameRes3Error
    {
        NameRes3ErrKind kind{};
        FileId file{};
        ModuleId module{kInvalidModule};
        lex::Loc loc{};
        lex::SymId name{};
    };

    struct NameResolvePass3DB
    {
        std::vector<NameRes3Error> errors;

        // optional: useful later for mutability checks etc.
        struct LocalRec
        {
            ModuleId module{};
            lex::SymId name{};
            lex::Loc loc{};
            bool is_mut{false};
        };

        std::vector<LocalRec> locals;
    };

    static inline void pushErr(NameResolvePass3DB& out,
                               NameRes3ErrKind k,
                               FileId file,
                               ModuleId mod,
                               const lex::Loc& loc,
                               lex::SymId name = {})
    {
        out.errors.push_back(NameRes3Error{
            .kind = k,
            .file = file,
            .module = mod,
            .loc = loc,
            .name = name
        });
    }

    // --------------------------------------------
    // Local path access helpers
    // --------------------------------------------
    static inline llvm::ArrayRef<lex::SymId> getPathSegs(const hir::Arena& ar, hir::PathId pid)
    {
        return llvm::ArrayRef(ar.paths[(size_t)pid].path);
    }

    // --------------------------------------------
    // NameResolver: per-module runner
    // --------------------------------------------
    class NameResolver final
    {
    public:
        NameResolver(const ModulePassDB& p1,
                     const ScopePass2DB& p2,
                     hir::ArenaHolder& holder,
                     NameResolvePass3DB& out,
                     ModuleId mid)
            : p1_(p1), p2_(p2), holder_(holder), out_(out), mid_(mid)
        {
            const auto& mr = p1_.modules[(size_t)mid_];
            file_ = mr.file;
            ar_ = &holder_.arenas_[(size_t)mr.arena_index];
        }

        void run()
        {
            buildMethodHirIndex_();

            // Resolve all top-level decls in this module:
            for (hir::DeclId did : ar_->module.decls)
                resolveDecl_(did);
        }

    private:
        const ModulePassDB& p1_;
        const ScopePass2DB& p2_;
        hir::ArenaHolder& holder_;
        NameResolvePass3DB& out_;

        ModuleId mid_{kInvalidModule};
        FileId file_{};
        hir::Arena* ar_{nullptr};

        // quick access
        const ModuleScope& curScope_() const { return p2_.module_scopes[(size_t)mid_]; }
        const ModuleScope& scope_(ModuleId m) const { return p2_.module_scopes[(size_t)m]; }

        // Generic binder visibility stack
        llvm::SmallVector<BinderId, 8> binder_stack_;

        // Lexical locals scopes
        struct LocalBinding
        {
            uint32_t local_id{};
            bool is_mut{};
            lex::Loc loc{};
        };

        llvm::SmallVector<llvm::DenseMap<lex::SymId, LocalBinding>, 16> local_scopes_;

        // MethodId (HIR) -> Pass2 MethodRec index (sema::MethodId)
        llvm::DenseMap<hir::MethodId, MethodId> method_by_hir_;

        // --------------------------------------------
        // Binder stack
        // --------------------------------------------
        void pushBinder_(BinderId b) { if (b != kInvalidBinder) binder_stack_.push_back(b); }
        void popBinder_(BinderId b) { if (b != kInvalidBinder) binder_stack_.pop_back(); }

        std::optional<std::pair<BinderId, SemaParamIndex>> lookupTypeParam_(lex::SymId name) const
        {
            for (int i = static_cast<int>(binder_stack_.size()) - 1; i >= 0; --i)
            {
                const BinderId bid = binder_stack_[static_cast<size_t>(i)];
                const auto& b = p2_.binders[static_cast<size_t>(bid)];
                auto it = b.params_by_name.find(name);
                if (it != b.params_by_name.end())
                    return std::pair{bid, it->second};
            }

            return std::nullopt;
        }

        // --------------------------------------------
        // Local scopes
        // --------------------------------------------
        void enterScope_() { local_scopes_.push_back(llvm::DenseMap<lex::SymId, LocalBinding>{}); }
        void leaveScope_() { local_scopes_.pop_back(); }

        std::optional<LocalBinding> lookupLocal_(lex::SymId name) const
        {
            for (int i = static_cast<int>(local_scopes_.size()) - 1; i >= 0; --i)
            {
                auto& m = local_scopes_[(size_t)i];
                auto it = m.find(name);
                if (it != m.end()) return it->second;
            }

            return std::nullopt;
        }

        void declareLocal_(lex::SymId name, const lex::Loc& loc, bool is_mut)
        {
            if (local_scopes_.empty()) enterScope_();

            auto& top = local_scopes_.back();
            if (top.find(name) != top.end())
            {
                pushErr(out_, NameRes3ErrKind::DuplicateLocalName, file_, mid_, loc, name);
                return;
            }

            const uint32_t id = static_cast<uint32_t>(out_.locals.size());
            out_.locals.push_back({.module = mid_, .name = name, .loc = loc, .is_mut = is_mut});

            top.try_emplace(name, LocalBinding{.local_id = id, .is_mut = is_mut, .loc = loc});
        }

        // --------------------------------------------
        // Qualified lookup policy (CLEAN)
        //
        // If segs.size()>1: first segment must be an import binding
        // (because Pass 2 already normalized import alias binding).
        //
        // No global module-tree absolute resolution here: keep it clean.
        // --------------------------------------------
        std::optional<ModuleId> resolveQualifierModule_(lex::SymId qualifier) const
        {
            auto it = curScope_().imports.find(qualifier);
            if (it == curScope_().imports.end()) return std::nullopt;

            // assume pass1+pass2 ok => target is valid
            return it->second.target;
        }

        const Symbol* lookupTypeSymbol_(ModuleId m, lex::SymId name) const
        {
            auto& sc = scope_(m);
            if (auto it = sc.types.find(name); it != sc.types.end())
                return &it->second;

            if (auto itp = p2_.prelude.types.find(name); itp != p2_.prelude.types.end())
                return &itp->second;

            return nullptr;
        }

        const Symbol* lookupValueSymbol_(ModuleId m, lex::SymId name) const
        {
            auto& sc = scope_(m);
            if (auto it = sc.values.find(name); it != sc.values.end())
                return &it->second;

            // prelude values can be added later
            return nullptr;
        }

        // --------------------------------------------
        // Resolve TYPE (TypeId)
        // --------------------------------------------
        void resolveType_(hir::TypeId tid)
        {
            auto& t = ar_->types[(size_t)tid];
            std::visit([&]<typename T0>(T0& node)
            {
                using T = std::decay_t<T0>;

                if constexpr (std::is_same_v<T, hir::TypeBuiltin>)
                {
                    // already resolved by construction
                }
                else if constexpr (std::is_same_v<T, hir::TypeRef>)
                {
                    resolveType_(node.inner);
                }
                else if constexpr (std::is_same_v<T, hir::TypeArray>)
                {
                    resolveType_(node.elem);
                    resolveExpr_(node.size); // size expr can contain names
                }
                else if constexpr (std::is_same_v<T, hir::TypePath>)
                {
                    resolveTypePath_(node);
                }
            }, t.kind);
        }

        void resolveTypePath_(hir::TypePath& tp)
        {
            // resolve targs
            for (hir::TypeId a : tp.targs) resolveType_(a);

            // path expression must be ExprPath
            auto& pe = ar_->exprs[(size_t)tp.path];
            if (!std::holds_alternative<hir::ExprPath>(pe.kind))
            {
                pushErr(out_, NameRes3ErrKind::NotAType, file_, mid_, tp.loc);
                return;
            }

            auto& ep = std::get<hir::ExprPath>(pe.kind);
            auto segs = getPathSegs(*ar_, ep.path);

            // 1) type param
            if (segs.size() == 1)
            {
                if (const auto tv = lookupTypeParam_(segs[0]))
                {
                    // Use your existing TypeResKind/TypeResId encoding.
                    // Here: TypeParam is stored as (binder, index) in id.
                    const uint32_t enc = (tv->first << 16) | static_cast<uint32_t>(tv->second);

                    tp.res.kind = hir::TypeResKind::TypeParam;
                    tp.res.id = static_cast<hir::TypeResId>(enc);
                    tp.res.module = mid_;
                    return;
                }
            }

            // 2) module-qualified: ImportAlias::TypeName
            ModuleId target = mid_;
            lex::SymId name{};

            if (segs.size() == 1)
            {
                name = segs[0];
            }
            else
            {
                auto qm = resolveQualifierModule_(segs[0]);
                if (!qm.has_value())
                {
                    pushErr(out_, NameRes3ErrKind::UnresolvedTypeName, file_, mid_, tp.loc, segs.back());
                    return;
                }
                target = *qm;
                name = segs.back();
            }

            const Symbol* sym = lookupTypeSymbol_(target, name);
            if (!sym)
            {
                pushErr(out_, NameRes3ErrKind::UnresolvedTypeName, file_, mid_, tp.loc, name);
                return;
            }

            // arity check
            if (static_cast<uint32_t>(sym->arity) != tp.targs.size())
                pushErr(out_, NameRes3ErrKind::GenericArityMismatch, file_, mid_, tp.loc, name);

            // kind check + write
            if (sym->kind == SymKind::Struct)
            {
                tp.res.kind = hir::TypeResKind::Struct;
                tp.res.id = static_cast<hir::TypeResId>(sym->id);
                tp.res.module = target;
            }
            else if (sym->kind == SymKind::Trait)
            {
                tp.res.kind = hir::TypeResKind::Trait;
                tp.res.id = static_cast<hir::TypeResId>(sym->id);
                tp.res.module = target;
            }
            // else if (sym->kind == SymKind::TypeAlias)
            // {
            //     tp.res.kind = hir::TypeResKind::TypeAlias;
            //     tp.res.id = static_cast<hir::TypeResId>(sym->id);
            //     tp.res.module = target;
            // }
            else
            {
                pushErr(out_, NameRes3ErrKind::NotAType, file_, mid_, tp.loc, name);
            }
        }

        // --------------------------------------------
        // Resolve EXPR (ExprId)
        // --------------------------------------------
        void resolveExpr_(hir::ExprId eid)
        {
            auto& e = ar_->exprs[(size_t)eid];

            std::visit([&]<typename T0>(T0& node)
            {
                using T = std::decay_t<T0>;

                if constexpr (std::is_same_v<T, hir::ExprPath>)
                {
                    resolveExprPath_(node);
                }
                else if constexpr (std::is_same_v<T, hir::ExprUnary>)
                {
                    resolveExpr_(node.rhs);
                }
                else if constexpr (std::is_same_v<T, hir::ExprBinary>)
                {
                    resolveExpr_(node.lhs);
                    resolveExpr_(node.rhs);
                }
                else if constexpr (std::is_same_v<T, hir::ExprAssign>)
                {
                    resolveExpr_(node.lhs);
                    resolveExpr_(node.rhs);
                }
                else if constexpr (std::is_same_v<T, hir::ExprCall>)
                {
                    resolveExpr_(node.callee);
                    for (hir::ExprId a : node.args) resolveExpr_(a);
                    // If your ExprCall.targs become TypeId later, resolveType_ on them here.
                }
                else if constexpr (std::is_same_v<T, hir::ExprIndex>)
                {
                    resolveExpr_(node.base);
                    resolveExpr_(node.index);
                }
                else if constexpr (std::is_same_v<T, hir::ExprField>)
                {
                    resolveExpr_(node.base);
                }
                else if constexpr (std::is_same_v<T, hir::ExprLitArray>)
                {
                    for (hir::ExprId el : node.elements) resolveExpr_(el);
                }
                else if constexpr (std::is_same_v<T, hir::ExprLitStruct>)
                {
                    resolveExpr_(node.type);
                    resolveStructLitType_(node);

                    for (hir::FieldInitId f : node.fields)
                    {
                        auto& fi = ar_->field_inits[(size_t)f];
                        resolveExpr_(fi.value);
                    }
                }
                else if constexpr (std::is_same_v<T, hir::ExprCast>)
                {
                    resolveExpr_(node.expr);
                    resolveType_(node.type);
                }
                else
                {
                    // literals: no resolution needed
                }
            }, e.kind);
        }

        void resolveExprPath_(hir::ExprPath& ep)
        {
            auto segs = getPathSegs(*ar_, ep.path);

            // 1) single segment: locals -> (params) -> module values -> type-name fallback
            if (segs.size() == 1)
            {
                const lex::SymId n = segs[0];

                if (auto lb = lookupLocal_(n))
                {
                    ep.res.kind = hir::ValueResKind::Local;
                    ep.res.id = lb->local_id;
                    ep.res.module = mid_;
                    return;
                }

                // TODO: parameters if you build param bindings as locals
                // if you do that, you get Param resolution “for free” via lookupLocal_.

                if (const Symbol* vs = lookupValueSymbol_(mid_, n))
                {
                    ep.res.module = mid_;
                    ep.res.id = static_cast<hir::ValueResId>(vs->id);
                    ep.res.kind = (vs->kind == SymKind::LoadFn)
                                      ? hir::ValueResKind::LoadFn
                                      : hir::ValueResKind::Fn;
                    return;
                }

                // allow type names in expr position (for struct literals / constructors)
                if (const Symbol* ts = lookupTypeSymbol_(mid_, n))
                {
                    ep.res.module = mid_;
                    ep.res.id = static_cast<hir::ValueResId>(ts->id);
                    ep.res.kind = hir::ValueResKind::TypeName;
                    return;
                }

                pushErr(out_, NameRes3ErrKind::UnresolvedValueName, file_, mid_, ep.loc, n);
                return;
            }

            // 2) qualified: ImportAlias::Name
            auto qm = resolveQualifierModule_(segs[0]);
            if (!qm.has_value())
            {
                pushErr(out_, NameRes3ErrKind::UnresolvedValueName, file_, mid_, ep.loc, segs.back());
                return;
            }

            const ModuleId target = *qm;
            const lex::SymId last = segs.back();

            if (const Symbol* vs = lookupValueSymbol_(target, last))
            {
                ep.res.module = target;
                ep.res.id = static_cast<hir::ValueResId>(vs->id);
                ep.res.kind = (vs->kind == SymKind::LoadFn)
                                  ? hir::ValueResKind::LoadFn
                                  : hir::ValueResKind::Fn;
                return;
            }

            if (const Symbol* ts = lookupTypeSymbol_(target, last))
            {
                ep.res.module = target;
                ep.res.id = static_cast<hir::ValueResId>(ts->id);
                ep.res.kind = hir::ValueResKind::TypeName;
                return;
            }

            pushErr(out_, NameRes3ErrKind::UnresolvedValueName, file_, mid_, ep.loc, last);
        }

        void resolveStructLitType_(hir::ExprLitStruct& ls)
        {
            // ls.type should be ExprPath resolving to TypeName
            auto& te = ar_->exprs[(size_t)ls.type];
            if (!std::holds_alternative<hir::ExprPath>(te.kind)) return;

            auto& ep = std::get<hir::ExprPath>(te.kind);
            if (ep.res.kind != hir::ValueResKind::TypeName) return;

            // derive actual type kind by re-looking up last segment in type namespace
            auto segs = getPathSegs(*ar_, ep.path);
            ModuleId target = ep.res.module;
            lex::SymId last = segs.back();

            const Symbol* ts = lookupTypeSymbol_(target, last);
            if (!ts) return;

            if (ts->kind == SymKind::Struct)
            {
                ls.type_res.kind = hir::TypeResKind::Struct;
                ls.type_res.id = static_cast<hir::TypeResId>(ts->id);
                ls.type_res.module = target;
            }
            else if (ts->kind == SymKind::Trait)
            {
                ls.type_res.kind = hir::TypeResKind::Trait;
                ls.type_res.id = static_cast<hir::TypeResId>(ts->id);
                ls.type_res.module = target;
            }
            // else if (ts->kind == SymKind::TypeAlias)
            // {
            //     ls.type_res.kind = hir::TypeResKind::TypeAlias;
            //     ls.type_res.id = (hir::TypeResId)ts->id;
            //     ls.type_res.module = target;
            // }
        }

        // --------------------------------------------
        // Statements / blocks
        // --------------------------------------------
        void resolveBlock_(hir::BlockId bid)
        {
            auto& b = ar_->blocks[(size_t)bid];
            enterScope_();
            for (hir::StmtId sid : b.stmts) resolveStmt_(sid);
            leaveScope_();
        }

        void resolveStmt_(hir::StmtId sid)
        {
            auto& s = ar_->stmts[static_cast<size_t>(sid)];

            std::visit([&]<typename T0>(T0& node)
            {
                using ST = std::decay_t<T0>;

                if constexpr (std::is_same_v<ST, hir::StmtBlock>)
                {
                    resolveBlock_(node.block);
                }
                else if constexpr (std::is_same_v<ST, hir::StmtIf>)
                {
                    resolveExpr_(node.cond);
                    resolveBlock_(node.then_blk);
                    // adapt for else-if/else blocks if you store them
                }
                else if constexpr (std::is_same_v<ST, hir::StmtWhile>)
                {
                    resolveExpr_(node.cond);
                    resolveBlock_(node.body);
                }
                else if constexpr (std::is_same_v<ST, hir::StmtDoWhile>)
                {
                    resolveBlock_(node.body);
                    resolveExpr_(node.cond);
                }
                else if constexpr (std::is_same_v<ST, hir::StmtReturn>)
                {
                    if (node.value.has_value()) resolveExpr_(*node.value);
                }
                else if constexpr (std::is_same_v<ST, hir::StmtExpr>)
                {
                    resolveExpr_(node.expr);
                }
                else if constexpr (std::is_same_v<ST, hir::StmtVar>)
                {
                    // ADAPT: field names may differ in your StmtVar
                    if constexpr (requires { node.type; }) resolveType_(node.type);
                    if constexpr (requires { node.init; })
                    {
                        if (node.init.has_value()) resolveExpr_(*node.init);
                    }

                    bool is_mut = false;
                    if constexpr (requires { node.mut; }) is_mut = (node.mut == ast::Mutability::Mut);
                    if constexpr (requires { node.mutability; }) is_mut = (node.mutability == ast::Mutability::Mut);

                    if constexpr (requires { node.name; node.loc; })
                        declareLocal_(node.name, node.loc, is_mut);
                }
                else
                {
                    // break/continue etc.
                }
            }, s.kind);
        }

        // --------------------------------------------
        // Decl traversal (NO pass1/pass2 checks duplicated)
        // --------------------------------------------
        void resolveDecl_(hir::DeclId did)
        {
            auto& d = ar_->decls[(size_t)did];

            std::visit([&]<typename T0>(T0& node)
            {
                using DT = std::decay_t<T0>;

                if constexpr (std::is_same_v<DT, hir::FnDecl>)
                {
                    // binder from pass2
                    if (auto it = p2_.fn_by_decl.find(did); it != p2_.fn_by_decl.end())
                        pushBinder_(p2_.fns[(size_t)it->second].binder);

                    enterScope_();
                    declareParamsAsLocals_(node.header);
                    resolveFnHeaderTypes_(node.header);
                    resolveBlock_(node.body);
                    leaveScope_();

                    if (auto it = p2_.fn_by_decl.find(did); it != p2_.fn_by_decl.end())
                        popBinder_(p2_.fns[(size_t)it->second].binder);
                }
                else if constexpr (std::is_same_v<DT, hir::LoadFnDecl>)
                {
                    resolveFnHeaderTypes_(node.header);
                }
                else if constexpr (std::is_same_v<DT, hir::StructDecl>)
                {
                    if (auto it = p2_.struct_by_decl.find(did); it != p2_.struct_by_decl.end())
                        pushBinder_(p2_.structs[(size_t)it->second].binder);

                    for (hir::FieldDeclId fid : node.fields)
                    {
                        auto& f = ar_->field_decls[(size_t)fid];
                        resolveType_(f.type);
                    }

                    if (auto it = p2_.struct_by_decl.find(did); it != p2_.struct_by_decl.end())
                        popBinder_(p2_.structs[(size_t)it->second].binder);
                }
                else if constexpr (std::is_same_v<DT, hir::TypeAliasDecl>)
                {
                    resolveType_(node.aliased);
                }
                else if constexpr (std::is_same_v<DT, hir::TraitDecl>)
                {
                    if (auto it = p2_.trait_by_decl.find(did); it != p2_.trait_by_decl.end())
                        pushBinder_(p2_.traits[(size_t)it->second].binder);

                    for (hir::MethodId hm : node.methods)
                        resolveMethod_(hm);

                    if (auto it = p2_.trait_by_decl.find(did); it != p2_.trait_by_decl.end())
                        popBinder_(p2_.traits[(size_t)it->second].binder);
                }
                else if constexpr (std::is_same_v<DT, hir::ImplDecl>)
                {
                    // impl binder (generic params visible to its methods)
                    if (auto it = p2_.impl_by_decl.find(did); it != p2_.impl_by_decl.end())
                        pushBinder_(p2_.impls[(size_t)it->second].binder);

                    // resolve header-level references only (no “impl exists” checks here)
                    if (node.trait_path.has_value()) resolveExpr_(*node.trait_path);
                    resolveType_(node.for_type);

                    for (hir::MethodId hm : node.methods)
                        resolveMethod_(hm);

                    if (auto it = p2_.impl_by_decl.find(did); it != p2_.impl_by_decl.end())
                        popBinder_(p2_.impls[(size_t)it->second].binder);
                }
            }, d.kind);
        }

        void resolveMethod_(hir::MethodId hm)
        {
            auto& m = ar_->methods[static_cast<size_t>(hm)];

            // push method binder if pass2 created one
            BinderId methodBinder = kInvalidBinder;
            if (auto it = method_by_hir_.find(hm); it != method_by_hir_.end())
            {
                const auto semaMid = it->second;
                methodBinder = p2_.methods[static_cast<size_t>(semaMid)].binder;
                pushBinder_(methodBinder);
            }

            std::visit([&]<typename T0>(T0& mn)
            {
                using MT = std::decay_t<T0>;

                if constexpr (std::is_same_v<MT, hir::TraitMethod>)
                {
                    enterScope_();
                    declareParamsAsLocals_(mn.header);
                    resolveFnHeaderTypes_(mn.header);
                    if (mn.body.has_value()) resolveBlock_(*mn.body);
                    leaveScope_();
                }
                else if constexpr (std::is_same_v<MT, hir::ImplMethod>)
                {
                    enterScope_();
                    declareParamsAsLocals_(mn.header);
                    resolveFnHeaderTypes_(mn.header);
                    resolveBlock_(mn.body);
                    leaveScope_();
                }
            }, m.kind);

            if (methodBinder != kInvalidBinder)
                popBinder_(methodBinder);
        }

        // --------------------------------------------
        // Fn header helpers (requires-friendly)
        // --------------------------------------------
        void declareParamsAsLocals_(hir::FnHeader& h)
        {
            if constexpr (requires { h.params; })
            {
                for (hir::ParamId pid : h.params)
                {
                    auto& p = ar_->params[static_cast<size_t>(pid)];
                    std::visit([&]<typename T0>(T0& pk)
                    {
                        using PK = std::decay_t<T0>;
                        if constexpr (std::is_same_v<PK, hir::ParamNamed>)
                        {
                            declareLocal_(pk.name, pk.loc, /*is_mut*/false);
                        }
                        else if constexpr (std::is_same_v<PK, hir::ParamSelf>)
                        {
                            // treat self as local; mut depends on kind if you want
                            declareLocal_(pk.name, pk.loc, /*is_mut*/false);
                        }
                    }, p.kind);
                }
            }
        }

        void resolveFnHeaderTypes_(hir::FnHeader& h)
        {
            if constexpr (requires { h.params; })
            {
                for (hir::ParamId pid : h.params)
                {
                    auto& p = ar_->params[static_cast<size_t>(pid)];
                    std::visit([&]<typename T0>(T0& pk)
                    {
                        using PK = std::decay_t<T0>;
                        if constexpr (std::is_same_v<PK, hir::ParamNamed>)
                        {
                            resolveType_(pk.type);
                        }
                        else if constexpr (std::is_same_v<PK, hir::ParamSelf>)
                        {
                            if (pk.explicit_type.has_value())
                                resolveType_(*pk.explicit_type);
                        }
                    }, p.kind);
                }
            }

            if constexpr (requires { h.return_type; })
                resolveType_(h.return_type);
        }

        // --------------------------------------------
        // Build HIR MethodId -> sema MethodId index once
        // --------------------------------------------
        void buildMethodHirIndex_()
        {
            method_by_hir_.clear();
            method_by_hir_.reserve(p2_.methods.size());

            for (MethodId i = 0; i < static_cast<MethodId>(p2_.methods.size()); ++i)
            {
                const auto& mr = p2_.methods[static_cast<size_t>(i)];
                if (mr.owner != mid_) continue;
                method_by_hir_.try_emplace(mr.hir_id, i);
            }
        }
    };

    // --------------------------------------------
    // Pass 3 entry point
    // --------------------------------------------
    inline NameResolvePass3DB runNameResolvePass3(const ModulePassDB& p1,
                                                  const ScopePass2DB& p2,
                                                  hir::ArenaHolder& holder)
    {
        NameResolvePass3DB out;

        const size_t n = std::min(holder.arenas_.size(), p1.modules.size());
        for (size_t i = 0; i < n; ++i)
        {
            const ModuleId mid = static_cast<ModuleId>(i);
            NameResolver r(p1, p2, holder, out, mid);
            r.run();
        }

        return out;
    }
} // namespace sema

#endif // INZ_SEMA_NAME_RESOLVE_PASS3_HPP
