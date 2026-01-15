#ifndef INZ_ARENA_HPP
#define INZ_ARENA_HPP

#include <vector>
#include <llvm/ADT/ArrayRef.h>

#include "decls.hpp"
#include "core_deferring_visit.hpp"
#include "default_defering_visit.hpp"
#include "dump_visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"
#include "iterator.hpp"
#include "hir/metadata.hpp"

namespace hir
{
    struct Arena final
    {
        std::vector<PathEntry> paths;

        Module module;
        std::vector<Import> imports;

        std::vector<TypeParam> tparams;
        std::vector<Param> params;

        std::vector<StructFieldDecl> field_decls;
        std::vector<StructFieldInit> field_inits;

        std::vector<Decl> decls;
        std::vector<Method> methods;

        std::vector<Type> types;
        std::vector<Expr> exprs;
        std::vector<Stmt> stmts;
        std::vector<Block> blocks;

        Arena() = default;

        Arena(Arena&& a) noexcept
            : paths(std::move(a.paths)), module(std::move(a.module)),
              imports(std::move(a.imports)), tparams(std::move(a.tparams)),
              params(std::move(a.params)), field_decls(std::move(a.field_decls)),
              field_inits(std::move(a.field_inits)), decls(std::move(a.decls)),
              methods(std::move(a.methods)),
              types(std::move(a.types)), exprs(std::move(a.exprs)),
              stmts(std::move(a.stmts)), blocks(std::move(a.blocks))
        {
        }

        Arena& operator=(Arena&& a) noexcept
        {
            if (&a != this)
            {
                paths = std::move(a.paths);
                module = std::move(a.module);
                imports = std::move(a.imports);
                tparams = std::move(a.tparams);
                params = std::move(a.params);
                field_decls = std::move(a.field_decls);
                field_inits = std::move(a.field_inits);
                decls = std::move(a.decls);
                methods = std::move(a.methods);
                types = std::move(a.types);
                exprs = std::move(a.exprs);
                stmts = std::move(a.stmts);
                blocks = std::move(a.blocks);
            }

            return *this;
        }
    };

    enum class ArenaKinds : size_t
    {
        imports,
        tparams,
        params,
        field_decls,
        field_inits,
        decls,
        methods,
        types,
        exprs,
        stmts,
        blocks
    };

    template <
        template<typename> typename AVisitor,
        typename... MetaData
    >
    using ArenaIterator = Iterator<
        DefaultDeferingVisitor,
        AVisitor,
        ArenaKinds,
        uint32_t,
        Arena,
        std::tuple<MetaData...>,
        &Arena::imports,
        &Arena::tparams,
        &Arena::params,
        &Arena::field_decls,
        &Arena::field_inits,
        &Arena::decls,
        &Arena::methods,
        &Arena::types,
        &Arena::exprs,
        &Arena::stmts,
        &Arena::blocks
    >;

    using DIterator = hir::ArenaIterator<
        DumpVisitor,
        MetaData
    >;

    template <
        template<typename> typename CVisitor,
        template<typename> typename AVisitor,
        typename... MetaData
    >
    using PartialIterator = Iterator<
        CVisitor,
        AVisitor,
        ArenaKinds,
        uint32_t,
        Arena,
        std::tuple<MetaData...>,
        &Arena::imports,
        &Arena::tparams,
        &Arena::params,
        &Arena::field_decls,
        &Arena::field_inits,
        &Arena::decls,
        &Arena::methods,
        &Arena::types,
        &Arena::exprs,
        &Arena::stmts,
        &Arena::blocks
    >;

    static inline llvm::ArrayRef<lex::SymId>
    getPathSegsFromExprPath(hir::Arena& ar, hir::ExprId expr_id)
    {
        auto& exp = ar.exprs[expr_id];
        auto& ep = std::get<hir::ExprPath>(exp.kind);
        auto& pe = ar.paths[ep.path];

        return {pe.path.data(), pe.path.size()};
    }
}


#endif
