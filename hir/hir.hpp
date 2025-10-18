//
// Created by yhwach on 9/19/25.
//

#ifndef HIR_HPP
#define HIR_HPP

namespace hir {
    class hir final {
        std::vector<ast::ExprPtr> epxrs;
        std::vector<ast::StatementPtr> stmts;
        std::vector<ast::DeclPtr> decls;
        std::vector<ast::ModulePtr> modules;



    public:
        hir(Project* ast_root) {

        }

    };
}

#endif //HIR_HPP
