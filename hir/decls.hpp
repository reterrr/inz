#ifndef INZ_DECLS_HPP
#define INZ_DECLS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "fn_header.hpp"
#include "ids.hpp"

namespace hir
{
    struct FnDecl
    {
        FnHeader header;
        std::vector<TypeParamId> tparams;
        BlockId body;
        lex::Loc loc;

        bool exported;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct LoadFnDecl
    {
        FnHeader header;
        lex::Loc loc;
        bool exported;
    };

    struct StructDecl
    {
        lex::SymId name;
        std::vector<TypeParamId> tparams;
        std::vector<FieldDeclId> fields;
        lex::Loc loc;

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
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TraitDecl
    {
        lex::SymId name;
        std::vector<MethodId> methods;
        std::vector<TypeParamId> tparams;
        bool exported;
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ImplDecl
    {
        std::optional<ExprId> trait_path;
        TypeId for_type;
        lex::Loc loc;

        std::vector<MethodId> methods;
        std::vector<TypeParamId> tparams;

        template <typename V>
        void accept(V& v) { v.visit(*this); }
    };

    using DeclKind = std::variant<
        FnDecl,
        LoadFnDecl,
        StructDecl,
        TypeAliasDecl,
        TraitDecl,
        ImplDecl
    >;

    struct Decl
    {
        DeclKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
