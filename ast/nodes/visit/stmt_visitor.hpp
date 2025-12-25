//
// Created by yhwach on 8/29/25.
//

#ifndef STATEMENT_VISITOR_HPP
#define STATEMENT_VISITOR_HPP

#include "visitor.hpp"

namespace ast
{
    struct IfStatement;
    struct ElseIfStatement;
    struct ElseStatement;
    struct WhileStatement;
    struct DoWhileStatement;
    struct BlockStatement;
    struct ReturnStatement;
    struct ExprStatement;
    struct ContinueStatement;
    struct BreakStatement;
    struct VarStmt;
}

namespace ast::visitor
{
    struct StmtVisitor
        : Visitor<IfStatement, ElseIfStatement, ElseStatement,
                  BlockStatement, WhileStatement,
                  ReturnStatement, ExprStatement, VarStmt,
                  ContinueStatement, BreakStatement, DoWhileStatement>
    {
    };
}

#endif //STATEMENT_VISITOR_HPP
