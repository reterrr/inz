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
        lex::Loc loc;

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
        lex::Loc loc;

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
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtElse
    {
        BlockId blk;
        lex::Loc loc;

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
        lex::Loc loc;

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
        lex::Loc loc;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtBreak
    {
        lex::Loc loc;
        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtContinue
    {
        lex::Loc loc;
        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };

    struct StmtReturn
    {
        std::optional<ExprId> value;
        lex::Loc loc;

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
        lex::Loc loc;

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
        StmtKind kind;

        template <typename V>
        void accept(V& v)
        {
            v.visit(*this);
        }
    };
}

#endif
