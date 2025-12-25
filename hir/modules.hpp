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

    struct Param
    {
        lex::Loc loc;
        lex::SymId name;
        TypeId type;

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

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
