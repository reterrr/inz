#ifndef INZ_STMTS_HPP
#define INZ_STMTS_HPP

#include <optional>
#include <variant>
#include <vector>

#include "ids.hpp"
#include "token.hpp"
#include "modules.hpp"

namespace hir
{
    enum class BlockKind { Anon, Fn, If, ElseIf, Else, While, DoWhile };

    struct StmtBlock
    {
        BlockId block;
        BlockKind kind;
    };

    struct StmtIf
    {
        ExprId cond;
        BlockId then_blk;
        std::vector<StmtId> elseifs;
        std::optional<BlockId> else_blk;
    };

    struct StmtElseIf
    {
        ExprId cond;
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
        Mutability mut;
        StorageClass storage;
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
