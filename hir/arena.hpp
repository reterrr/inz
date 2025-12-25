#ifndef INZ_ARENA_HPP
#define INZ_ARENA_HPP

#include <vector>

#include "decls.hpp"
#include "dfs_deferring_visit.hpp"
#include "dump_visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"
#include "iterator.hpp"

namespace hir
{
    struct Arena final
    {
        std::vector<PathEntry> paths;

        std::vector<Module> modules;
        std::vector<Import> imports;

        std::vector<TypeParam> tparams;
        std::vector<Param> params;

        std::vector<StructFieldDecl> field_decls;
        std::vector<StructFieldInit> field_inits;

        std::vector<Decl> decls;

        std::vector<Type> types;
        std::vector<Expr> exprs;
        std::vector<Stmt> stmts;
        std::vector<Block> blocks;
    };

    inline auto getView(Arena& a)
    {
        return std::tuple(
            &Arena::modules, a.imports, a.tparams,
            a.params, a.field_decls, a.field_inits,
            a.decls, a.types, a.exprs,
            a.stmts, a.blocks
        );
    }

    enum class ArenaKinds : size_t
    {
        modules,
        imports,
        tparams,
        params,
        field_decls,
        field_inits,
        decls,
        types,
        exprs,
        stmts,
        blocks
    };

    using DIterator = hir::Iterator<
        DFSDeferringChildVisitor,
        DumpVisitor,
        ArenaKinds,
        uint32_t,
        Arena,
        &Arena::modules,
        &Arena::imports,
        &Arena::tparams,
        &Arena::params,
        &Arena::field_decls,
        &Arena::field_inits,
        &Arena::decls,
        &Arena::types,
        &Arena::exprs,
        &Arena::stmts,
        &Arena::blocks
    >;
}


#endif
