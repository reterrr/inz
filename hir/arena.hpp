#ifndef INZ_ARENA_HPP
#define INZ_ARENA_HPP

#include <vector>

#include "decls.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"

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
}

#endif
