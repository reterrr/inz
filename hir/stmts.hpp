#ifndef INZ_STMTS_HPP
#define INZ_STMTS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"

#include "stmt/block_stmt_kind.hpp"
#include "nodes/stmt/var_mutablity_storage.hpp"

namespace hir
{
    struct StmtBlock
    {
        BlockId block;
        ast::BlockKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtIf
    {
        ExprId cond;
        BlockId then_blk;
        std::vector<StmtId> elseifs;
        std::optional<StmtId> else_;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtElseIf
    {
        ExprId cond;
        BlockId blk;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtElse
    {
        BlockId blk;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtWhile
    {
        ExprId cond;
        BlockId body;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtDoWhile
    {
        BlockId body;
        ExprId cond;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtBreak
    {
        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtContinue
    {
        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtReturn
    {
        std::optional<ExprId> value;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtVar
    {
        lex::Loc loc;
        lex::SymId name;
        ast::Mutability mut;
        ast::Storage storage;
        TypeId type;
        std::optional<ExprId> init;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtExpr
    {
        ExprId expr;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    using StmtKind = std::variant<
        StmtBlock,
        StmtIf,
        StmtElseIf,
        StmtElse,
        StmtWhile,
        StmtDoWhile,
        StmtBreak,
        StmtContinue,
        StmtReturn,
        StmtVar,
        StmtExpr
    >;

    struct Stmt
    {
        lex::Loc loc;
        StmtKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
