#ifndef INZ_STMTS_HPP
#define INZ_STMTS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "token.hpp"
#include "stmt/block_stmt_kind.hpp"

namespace hir
{
    struct StmtBlock
    {
        BlockId block;
        ast::BlockKind kind;
    };

    struct StmtIf
    {
        ExprId cond;
        BlockId then_blk;
        std::vector<StmtId> elseifs;
        std::optional<StmtId> else_;
    };

    struct StmtElseIf
    {
        ExprId cond;
        BlockId blk;
    };

    struct StmtElse
    {
        BlockId blk;
    };

    struct StmtWhile
    {
        ExprId cond;
        BlockId body;
    };

    struct StmtDoWhile
    {
        BlockId body;
        ExprId cond;
    };

    struct StmtBreak
    {
    };

    struct StmtContinue
    {
    };

    struct StmtReturn
    {
        std::optional<ExprId> value;
    };

    struct StmtVar
    {
        lex::Loc loc;
        lex::SymId name;
        ast::Mutability mut;
        ast::Storage storage;
        TypeId type;
        std::optional<ExprId> init;
    };

    struct StmtExpr
    {
        ExprId expr;
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
    };
}

#endif
