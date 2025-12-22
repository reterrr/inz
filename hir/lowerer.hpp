//
// Created by yhwach on 12/22/25.
//

#ifndef INZ_LOWERER_HPP
#define INZ_LOWERER_HPP
#include <stack>

#include "arena.hpp"
#include "translation.hpp"

namespace hir
{
    class Lowerer final
    {
        Arena arena_;
        Translation& translation_;
        ast::Ast& ast_;

        Lowerer(ast::Ast& ast)
        {
            arena_.modules.reserve(ast.module_count());
            arena_.decls.reserve(ast.decl_count());
            arena_.stmts.reserve(ast.stmt_count());
            arena_.exprs.reserve(ast.expr_count());
            arena_.types.reserve(ast.type_count());

            arena_.tparams.reserve(ast.count(NodeKind::Decl_TypeParam));
            arena_.field_inits.reserve(ast.count(NodeKind::Expr_FieldInit));
            arena_.types.reserve(ast.count(NodeKind::Expr_Type));
            arena_.field_decls.reserve(ast.count(NodeKind::Decl_Field));
            arena_.blocks.reserve(ast.count(NodeKind::Stmt_Block));
            arena_.imports.reserve(ast.count(NodeKind::Decl_Import));
            arena_.params.reserve(ast.count(NodeKind::Decl_Param));
            arena_.paths.reserve(ast.count(NodeKind::Expr_Path));
        }


        void lower()
        {
            std::stack<ast::Node*> stack;

            for (auto module : translation_.units)
            {
                stack.push(module.module);
            }
        }
    };
}

#endif //INZ_LOWERER_HPP
