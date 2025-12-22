#ifndef INZ_DECLS_HPP
#define INZ_DECLS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "inz_module.hpp"
#include "token.hpp"

namespace hir
{
    struct FnDecl
    {
        std::vector<ParamId> params;
        TypeId return_type;
        std::optional<BlockId> body;
    };

    struct StructDecl
    {
        std::optional<std::vector<FieldDeclId>> fields;
    };

    struct TypeAliasDecl
    {
        TypeId aliased;
    };

    using DeclKind = std::variant<FnDecl, StructDecl, TypeAliasDecl>;

    struct Decl
    {
        lex::Loc loc;
        ModuleId mod;
        lex::SymId name;
        PathId full_path;
        std::vector<TypeParamId> tparams;
        Visibility vis;
        DeclKind kind;
    };
}

#endif
