#ifndef INZ_MODULE_HPP
#define INZ_MODULE_HPP

#include <optional>
#include <vector>

#include "ids.hpp"
#include "token.hpp"

namespace hir
{
    enum class StorageClass : uint8_t
    {
        Auto,
        Static
    };

    enum class Mutability : uint8_t
    {
        Imm,
        Mut
    };

    enum class Visibility : uint8_t
    {
        Private,
        Public
    };

    struct Module
    {
        lex::Loc loc;
        PathId package_path;
        std::vector<ImportId> imports;
        std::vector<DeclId> decls;
    };

    struct Import
    {
        lex::Loc loc;
        PathId path;
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
        Mutability mut;
    };

    struct StructFieldDecl
    {
        lex::Loc loc;
        lex::SymId name;
        TypeId type;
        Visibility vis;
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
