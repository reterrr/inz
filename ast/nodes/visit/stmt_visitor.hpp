//
// Created by yhwach on 8/29/25.
//

#ifndef STATEMENT_VISITOR_HPP
#define STATEMENT_VISITOR_HPP

#include "visitor.hpp"

namespace ast {
    struct IfStatement;
    struct WhileStatement;
    struct DoWhileStatement;
    struct BlockStatement;
    struct VarDeclStatement;
    struct ReturnStatement;
    struct ExprStatement;
    struct ContinueStatement;
    struct BreakStatement;
}

namespace ast::visitor {
    struct StmtVisitor
            : Visitor<IfStatement, BlockStatement, WhileStatement,
                VarDeclStatement, ReturnStatement, ExprStatement,
                ContinueStatement, BreakStatement, DoWhileStatement> {
    };
}

#endif //STATEMENT_VISITOR_HPP
