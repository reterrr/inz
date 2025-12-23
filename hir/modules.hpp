#ifndef INZ_MODULE_HPP
#define INZ_MODULE_HPP

#include <optional>
#include <vector>

#include "field_visibility.hpp"
#include "ids.hpp"
#include "token.hpp"

namespace hir
{
    struct Module
    {
        lex::Loc loc;
        ExprId package_path;
        std::vector<ImportId> imports;
        std::vector<DeclId> decls;
    };

    struct Import
    {
        lex::Loc loc;
        ExprId path;
        std::optional<lex::SymId> alias;
    };

    struct TypeParam
    {
        lex::Loc loc;
        lex::SymId name;
    };

    struct Param
    {
        lex::Loc loc;
        lex::SymId name;
        TypeId type;
    };

    struct StructFieldDecl
    {
        lex::Loc loc;
        lex::SymId name;
        TypeId type;
        ast::Visibility vis;
    };

    struct StructFieldInit
    {
        lex::Loc loc;
        lex::SymId name;
        ExprId value;
    };

    struct Block
    {
        lex::Loc loc;
        std::vector<StmtId> stmts;
    };
}

#endif
