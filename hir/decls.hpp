#ifndef INZ_DECLS_HPP
#define INZ_DECLS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"

namespace hir
{
    struct FnDecl
    {
        lex::SymId name;
        std::vector<TypeParamId> tparams;
        std::vector<ParamId> params;
        TypeId return_type;
        std::optional<BlockId> body;
        bool exported;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StructDecl
    {
        lex::SymId name;
        std::vector<TypeParamId> tparams;
        std::vector<FieldDeclId> fields;
        bool exported;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypeAliasDecl
    {
        TypeId aliased;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    using DeclKind = std::variant<FnDecl, StructDecl, TypeAliasDecl>;

    struct Decl
    {
        lex::Loc loc;
        DeclKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
