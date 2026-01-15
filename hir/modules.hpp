#ifndef INZ_MODULE_HPP
#define INZ_MODULE_HPP

#include <optional>
#include <vector>

#include "field_visibility.hpp"
#include "nodes/decl/self_param_kind.hpp"
#include "fn_header.hpp"
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

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct Import
    {
        lex::Loc loc;
        ExprId path;
        std::optional<lex::SymId> alias;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct TypeParam
    {
        lex::Loc loc;
        lex::SymId name;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ParamNamed
    {
        lex::SymId name;
        TypeId type; // required for named params
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct ParamSelf
    {
        ast::SelfParamKind kind; // your enum (Self, &Self, &mut Self, etc)
        lex::SymId name;
        std::optional<TypeId> explicit_type; // usually std::nullopt (type is inferred)
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    using ParamKind = std::variant<ParamNamed, ParamSelf>;

    struct Param
    {
        ParamKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StructFieldDecl
    {
        lex::Loc loc;
        lex::SymId name;
        TypeId type;
        ast::Visibility vis;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StructFieldInit
    {
        lex::Loc loc;
        lex::SymId name;
        ExprId value;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct Block
    {
        lex::Loc loc;
        std::vector<StmtId> stmts;
    };

    struct TraitMethod
    {
        FnHeader header;
        std::vector<TypeParamId> tparams;
        std::optional<BlockId> body;
        lex::Loc loc;
        bool exported{false};
    };

    struct ImplMethod
    {
        FnHeader header;
        std::vector<TypeParamId> tparams;
        BlockId body;
        lex::Loc loc;
        bool exported{false};
    };

    using MethodKind = std::variant<TraitMethod, ImplMethod>;

    struct Method
    {
        MethodKind kind;
    };
}

#endif
