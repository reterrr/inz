//
// Created by yhwach on 8/29/25.
//

#ifndef STATEMENT_VISITOR_HPP
#define STATEMENT_VISITOR_HPP

#include "visitor.hpp"

namespace ast
{
    struct IfStatement;
    struct WhileStatement;
    struct DoWhileStatement;
    struct BlockStatement;
    struct ReturnStatement;
    struct ExprStatement;
    struct ContinueStatement;
    struct BreakStatement;
    struct VarDeclStatement;
}

namespace ast::visitor
{
    struct StmtVisitor
        : Visitor<IfStatement, BlockStatement, WhileStatement,
                  ReturnStatement, ExprStatement, VarDeclStatement,
                  ContinueStatement, BreakStatement, DoWhileStatement>
    {
    };
}

#endif //STATEMENT_VISITOR_HPP
