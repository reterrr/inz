//
// Created by yhwach on 12/22/25.
//

#ifndef INZ_LOWERER_HPP
#define INZ_LOWERER_HPP

#include "arena.hpp"
#include "translation.hpp"
#include <llvm/ADT/DenseMap.h>

namespace hir
{
    class Lowerer final
    {
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

        Arena arena_;
        Translation& translation_;
        ast::Ast& ast_;

        std::vector<ast::Node*> stack;

        llvm::DenseMap<ast::Module*, ModuleId> modules;
        llvm::DenseMap<ast::Decl*, DeclId> decls;
        llvm::DenseMap<ast::Expr*, ExprId> exprs;
        llvm::DenseMap<ast::Statement*, StmtId> stmts;
        llvm::DenseMap<ast::ImportDecl*, ImportId> imports;
        llvm::DenseMap<ast::TypeExpr*, TypeId> types;
        llvm::DenseMap<ast::TypeParamDecl*, TypeParamId> typeParams;
        llvm::DenseMap<ast::BlockStatement*, BlockId> blocks;
        llvm::DenseMap<ast::FieldInitExpr*, FieldInitId> fieldInits;
        llvm::DenseMap<ast::FieldDecl*, FieldDeclId> fieldDecls;

        template <typename T>
        void defer_alloc(T* t)
        {
            stack.push_back(t);
        }

        template <typename T>
        void defer_alloc(const std::vector<T*>& ts)
        {
            stack.reserve(ts.rbegin() - ts.rend());
            stack.insert(stack.end(), ts.rbegin(), ts.rend());
        }

        void alloc_module(ast::Module* module)
        {
            auto moduleId = arena_.modules.size();
            modules.emplace_or_assign(module, moduleId);
            arena_.modules.push_back(Module{
                .loc = module->location_,
                .package_path = {},
                .imports = {},
                .decls = {}
            });

            defer_alloc(module->pathExpr_);
            defer_alloc(module->imports);
            defer_alloc(module->decls);
        }

        void alloc_import(ast::ImportDecl* imp)
        {
            auto importId = arena_.imports.size();
            imports.emplace_or_assign(imp, importId);
            arena_.imports.push_back(Import{
                .loc = imp->location_,
                .path = {},
                .alias = imp->alias
            });

            defer_alloc(imp->pathExpr_);
        }

        void alloc_struct(ast::StructDecl* decl)
        {
            auto structId = arena_.decls.size();
            decls.emplace_or_assign(decl, structId);
            arena_.decls.push_back(Decl{
                .loc = decl->location_,
                .name = decl->name_,
                .tparams = {},
                .exported = decl->isExported_,
                .kind = StructDecl{
                    .fields = {}
                }
            });
        }
    };
}

#endif //INZ_LOWERER_HPP
