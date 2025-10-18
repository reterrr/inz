//
// Created by yhwach on 9/25/25.
//

#ifndef DE_SUGAR_HPP
#define DE_SUGAR_HPP

namespace ast {
    class AST;
    struct ExprPtr;
    struct UnaryExpr;
}

namespace hir {
    class de_sugar final {
        de_sugar() = default;

        ast::ExprPtr de_sugar_post_increment_expr(ast::AST &ast, ast::UnaryExpr *&expr);

        ast::ExprPtr de_sugar_post_decrement_expr(ast::AST &ast, ast::UnaryExpr *&expr);

        ast::ExprPtr de_sugar_pre_increment_expr(ast::AST &ast, ast::UnaryExpr *&expr);

        ast::ExprPtr de_sugar_pre_decrement_expr(ast::AST &ast, ast::UnaryExpr *&expr);
    };
}

#endif //DE_SUGAR_HPP
