//
// Created by yhwach on 12/22/25.
//

#ifndef INZ_LOWERER_HPP
#define INZ_LOWERER_HPP

#include "arena.hpp"
#include "translation.hpp"
#include "types.hpp"
#include <llvm/ADT/DenseMap.h>

namespace hir
{
    class Lowerer final
    {
    public:
        Lowerer(ast::Ast& ast, Translation& translation)
            : translation_(translation), ast_(ast)
        {
            arena_.modules.reserve(ast.module_count());
            arena_.decls.reserve(ast.decl_count());
            arena_.stmts.reserve(ast.stmt_count());
            arena_.exprs.reserve(ast.expr_count());
            arena_.types.reserve(ast.type_count());

            arena_.tparams.reserve(ast.count(NodeKind::Decl_TypeParam));
            arena_.field_inits.reserve(ast.count(NodeKind::Expr_FieldInit));
            arena_.field_decls.reserve(ast.count(NodeKind::Decl_Field));
            arena_.blocks.reserve(ast.count(NodeKind::Stmt_Block));
            arena_.imports.reserve(ast.count(NodeKind::Decl_Import));
            arena_.params.reserve(ast.count(NodeKind::Decl_Param));
            arena_.paths.reserve(ast.count(NodeKind::Expr_Path));

            stack.reserve(ast_.node_count());
        }

        Arena arena_;
        Translation& translation_;
        ast::Ast& ast_;

        std::vector<ast::Node*> stack;

        llvm::DenseMap<ast::Module*, ModuleId> modules;
        llvm::DenseMap<ast::Decl*, DeclId> decls;
        llvm::DenseMap<ast::Expr*, ExprId> exprs;
        llvm::DenseMap<ast::ParamDecl*, ParamId> params;
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
            for (auto it = ts.rbegin(); it != ts.rend(); ++it)
                if (*it) stack.push_back(static_cast<ast::Node*>(*it));
        }

        template <typename Map, typename Key>
        auto get_id(Map& map, Key* key) -> Map::mapped_type
        {
            auto it = map.find(key);
            assert(it != map.end() && "requested id not allocated");
            return it->second;
        }

        template <typename Vec, typename Src, typename Map>
        void fill_id_vec(Vec& out, const std::vector<Src*>& srcs, Map& map)
        {
            out.reserve(out.size() + srcs.size());
            for (auto* s : srcs)
            {
                out.push_back(get_id(map, s));
            }
        }

        void alloc_expr_type(ast::TypeExpr* t)
        {
            assert(t && "alloc_expr_type: null");
            switch (t->kind_) // TypeExprKind
            {
            case ast::TypeExprKind::Builtin:
                alloc_type_builtin(static_cast<ast::BuiltinTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Array:
                alloc_type_array(static_cast<ast::ArrayTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Path:
                alloc_type_path(static_cast<ast::PathTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Ref:
                alloc_type_ref(static_cast<ast::RefTypeExpr*>(t));
                break;
            // case ast::TypeExprKind::Callable:
            //     alloc_type_callable(static_cast<ast::CallableTypeExpr*>(t));
            //     break;
            default:
                assert(false && "alloc_expr_type: unknown TypeExprKind");
            }
        }

        void alloc_expr_lit(ast::LiteralExpr* e)
        {
            assert(e && "alloc_expr_lit: null");
            switch (e->kind_) // LiteralKind
            {
            case kl::rt::LiteralKind::Int:
                alloc_expr_lit_int(static_cast<ast::IntLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Float:
                alloc_expr_lit_float(static_cast<ast::FloatLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::String:
                alloc_expr_lit_string(static_cast<ast::StringLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Bool:
                alloc_expr_lit_bool(static_cast<ast::BoolLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Char:
                alloc_expr_lit_char(static_cast<ast::CharLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Array:
                alloc_expr_lit_array(static_cast<ast::ArrayLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Struct:
                alloc_expr_lit_struct(static_cast<ast::StructLiteralExpr*>(e));
                break;
            default:
                assert(false && "alloc_expr_lit: unknown LiteralKind");
            }
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

            defer_alloc(decl->typeParamsDecls_);
            defer_alloc(decl->fields_);
        }

        // ---- Decls -------------------------------------------------------------
        void alloc_fndecl(ast::FunctionDecl* fn)
        {
            const auto declId = static_cast<DeclId>(arena_.decls.size());
            decls.emplace_or_assign(fn, declId);
            arena_.decls.push_back(Decl{
                .loc = fn->location_,
                .name = fn->name_,
                .tparams = {},
                .exported = fn->isExported_,
                .kind = FnDecl{
                    .params = {},
                    .return_type = {},
                    .body = std::nullopt
                }
            });

            defer_alloc(fn->typeParamsDecls_);
            defer_alloc(fn->params_);
            defer_alloc(fn->ret_);
            if (fn->body_) defer_alloc(fn->body_);
        }

        // void alloc_typealias(ast::TypeAliasDecl* decl)
        // {
        //     const auto declId = static_cast<DeclId>(arena_.decls.size());
        //     decls.emplace_or_assign(decl, declId);
        //     arena_.decls.push_back(Decl{
        //         .loc = decl->location_,
        //         .name = decl->type_name,
        //         .tparams = {},
        //         .exported = decl->isExported_,
        //         .kind = TypeAliasDecl{
        //             .aliased = {}
        //         }
        //     });
        //
        //     defer_alloc(decl->);
        //     defer_alloc(decl->aliasedType_);
        // }

        // ---- Type params / params / fields / path entries ---------------------
        void alloc_type_param(ast::TypeParamDecl* tp)
        {
            const auto id = static_cast<TypeParamId>(arena_.tparams.size());
            typeParams.emplace_or_assign(tp, id);
            arena_.tparams.push_back(TypeParam{
                .loc = tp->location_,
                .name = tp->name_
            });
        }

        void alloc_param(ast::ParamDecl* param)
        {
            const auto id = static_cast<ParamId>(arena_.params.size());
            params.emplace_or_assign(param, id);
            arena_.params.push_back(Param{
                .loc = param->location_,
                .name = param->name_,
                .type = {},
            });

            defer_alloc(param->type_);
        }

        void alloc_field_decl(ast::FieldDecl* field)
        {
            const auto id = static_cast<FieldDeclId>(arena_.field_decls.size());
            fieldDecls.emplace_or_assign(field, id);
            arena_.field_decls.push_back(StructFieldDecl{
                .loc = field->location_,
                .name = field->name_,
                .type = {},
                .vis = field->visibility_
            });

            defer_alloc(field->type_);
        }

        void alloc_field_init(ast::FieldInitExpr* init)
        {
            const auto id = static_cast<FieldInitId>(arena_.field_inits.size());
            fieldInits.emplace_or_assign(init, id);
            arena_.field_inits.push_back(StructFieldInit{
                .loc = init->location_,
                .name = init->name,
                .value = {}
            });

            defer_alloc(init->value_);
        }

        void alloc_expr_path(ast::PathExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            const auto pathId = static_cast<PathId>(arena_.paths.size());

            exprs.emplace_or_assign(e, id);

            arena_.paths.push_back(PathEntry{
                .path = e->path_,
            });

            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprPath{
                    .path = pathId,
                }
            });
        }

        // ---- Blocks -----------------------------------------------------------

        void alloc_stmt_block(ast::BlockStatement* s)
        {
            const auto sid = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, sid);

            const auto bid = static_cast<BlockId>(arena_.blocks.size());
            blocks.emplace_or_assign(s, bid);

            arena_.blocks.push_back(Block{
                .loc = s->location_,
                .stmts = {}
            });

            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtBlock{
                    .block = bid,
                    .kind = s->kind_
                }
            });

            defer_alloc(s->statements_);
        }

        void alloc_stmt_if(ast::IfStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtIf{
                    .cond = {},
                    .then_blk = {},
                    .elseifs = {},
                    .else_ = std::nullopt
                }
            });

            defer_alloc(s->condition_);
            defer_alloc(s->thenBody_);
            defer_alloc(s->elseIfs_);
            if (s->else_) defer_alloc(s->else_);
        }

        void alloc_stmt_elseif(ast::ElseIfStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtElseIf{
                    .cond = {},
                    .blk = {}
                }
            });

            defer_alloc(s->condition_);
            defer_alloc(s->then_);
        }

        void alloc_stmt_else(ast::ElseStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtElse{
                    .blk = {}
                }
            });

            defer_alloc(s->then_);
        }

        void alloc_stmt_while(ast::WhileStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtWhile{
                    .cond = {},
                    .body = {}
                }
            });

            defer_alloc(s->condition_);
            defer_alloc(s->body_);
        }

        void alloc_stmt_dowhile(ast::DoWhileStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtDoWhile{
                    .body = {},
                    .cond = {}
                }
            });

            defer_alloc(s->condition_);
            defer_alloc(s->body_);
        }

        void alloc_stmt_break(ast::BreakStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtBreak{}
            });
        }

        void alloc_stmt_continue(ast::ContinueStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtContinue{}
            });
        }

        void alloc_stmt_return(ast::ReturnStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtReturn{
                    .value = s->expr_ ? std::optional<ExprId>{} : std::nullopt
                }
            });

            defer_alloc(s->expr_);
        }

        void alloc_stmt_var(ast::VarStmt* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtVar{
                    .loc = s->location_,
                    .name = s->name_,
                    .mut = s->mut_,
                    .storage = s->storage_,
                    .type = {},
                    .init = s->init_ ? std::optional<ExprId>{} : std::nullopt
                }
            });

            defer_alloc(s->type_);
            if (s->init_) defer_alloc(s->init_);
        }

        void alloc_stmt_expr(ast::ExprStatement* s)
        {
            const auto id = static_cast<StmtId>(arena_.stmts.size());
            stmts.emplace_or_assign(s, id);
            arena_.stmts.push_back(Stmt{
                .loc = s->location_,
                .kind = StmtExpr{
                    .expr = {}
                }
            });

            defer_alloc(s->expr_);
        }

        void alloc_expr_lit_int(ast::IntLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitInt{
                    .sym = e->v_,
                    .kind = e->suffix_
                }
            });
        }

        void alloc_expr_lit_float(ast::FloatLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitFloat{
                    .sym = e->v_,
                    .kind = e->suffix_
                }
            });
        }

        void alloc_expr_lit_bool(ast::BoolLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitBool{
                    .value = e->v_
                }
            });
        }

        void alloc_expr_lit_char(ast::CharLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitChar{
                    .value = e->v_
                }
            });
        }

        void alloc_expr_lit_array(ast::ArrayLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitArray{
                    .elements = {}
                }
            });

            defer_alloc(e->v_);
        }

        void alloc_expr_lit_string(ast::StringLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitString{
                    .sym = e->v_
                }
            });
        }

        void alloc_expr_unary(ast::UnaryExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprUnary{
                    .op = e->op, // op mimatch
                    .rhs = {}
                }
            });

            defer_alloc(e->expr_);
        }

        void alloc_expr_binary(ast::BinaryExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprBinary{
                    .op = e->op,
                    .lhs = {},
                    .rhs = {}
                }
            });

            defer_alloc(e->lhs_);
            defer_alloc(e->rhs_);
        }

        void alloc_expr_assign(ast::AssignExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprAssign{
                    .op = e->op,
                    .lhs = {},
                    .rhs = {}
                }
            });

            defer_alloc(e->lhs_);
            defer_alloc(e->rhs_);
        }

        void alloc_expr_call(ast::CallExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprCall{
                    .callee = {},
                    .targs = {},
                    .args = {}
                }
            });

            defer_alloc(e->callee_);
            defer_alloc(e->typeArgs_);
            defer_alloc(e->args_);
        }

        void alloc_expr_index(ast::IndexExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprIndex{
                    .base = {},
                    .index = {}
                }
            });

            defer_alloc(e->base_);
            defer_alloc(e->index_);
        }

        void alloc_expr_field(ast::FieldExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprField{
                    .base = {},
                    .field = e->field
                }
            });

            defer_alloc(e->base_);
        }

        void alloc_expr_lit_struct(ast::StructLiteralExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprLitStruct{
                    .type = {},
                    .fields = {}
                }
            });

            defer_alloc(e->expr_);
            defer_alloc(e->elements_);
        }

        void alloc_expr_cast(ast::CastExpr* e)
        {
            const auto id = static_cast<ExprId>(arena_.exprs.size());
            exprs.emplace_or_assign(e, id);
            arena_.exprs.push_back(Expr{
                .loc = e->location_,
                .kind = ExprCast{
                    .expr = {},
                    .type = {}
                }
            });

            defer_alloc(e->source_);
            defer_alloc(e->targetSyntax_);
        }


        void alloc_type_builtin(ast::BuiltinTypeExpr* t)
        {
            const auto id = static_cast<TypeId>(arena_.types.size());
            types.emplace_or_assign(t, id);
            arena_.types.push_back(Type{
                .loc = t->location_,
                .kind = TypeBuiltin{.kind = t->kind_}
            });
        }

        void alloc_type_path(ast::PathTypeExpr* t)
        {
            const auto id = static_cast<TypeId>(arena_.types.size());
            types.emplace_or_assign(t, id);
            arena_.types.push_back(Type{
                .loc = t->location_,
                .kind = TypePath{
                    .path = {},
                    .targs = {}
                }
            });

            defer_alloc(t->pathExpr_);
            defer_alloc(t->typeArgs_);
        }

        void alloc_type_ref(ast::RefTypeExpr* t)
        {
            const auto id = static_cast<TypeId>(arena_.types.size());
            types.emplace_or_assign(t, id);
            arena_.types.push_back(Type{
                .loc = t->location_,
                .kind = TypeRef{
                    .mut = t->mut_,
                    .inner = {}
                }
            });

            defer_alloc(t->pointee_);
        }

        void alloc_type_array(ast::ArrayTypeExpr* t)
        {
            const auto id = static_cast<TypeId>(arena_.types.size());
            types.emplace_or_assign(t, id);
            arena_.types.push_back(Type{
                .loc = t->location_,
                .kind = TypeArray{
                    .elem = {},
                    .size = {}
                }
            });

            defer_alloc(t->type_);
            defer_alloc(t->sizeExpr_);
        }


        void fill_expr_lit(ast::LiteralExpr* e)
        {
            assert(e && "fill_expr_lit: null");
            switch (e->kind_) // LiteralKind
            {
            case kl::rt::LiteralKind::Int:
                fill_expr_lit_int(static_cast<ast::IntLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Float:
                fill_expr_lit_float(static_cast<ast::FloatLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::String:
                fill_expr_lit_string(static_cast<ast::StringLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Bool:
                fill_expr_lit_bool(static_cast<ast::BoolLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Char:
                fill_expr_lit_char(static_cast<ast::CharLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Array:
                fill_expr_lit_array(static_cast<ast::ArrayLiteralExpr*>(e));
                break;
            case kl::rt::LiteralKind::Struct:
                fill_expr_lit_struct(static_cast<ast::StructLiteralExpr*>(e));
                break;
            default:
                assert(false && "fill_expr_lit: unknown LiteralKind");
                break;
            }
        }

        void fill_expr_type(ast::TypeExpr* t)
        {
            assert(t && "fill_expr_type: null");
            switch (t->kind_) // TypeExprKind
            {
            case ast::TypeExprKind::Builtin:
                fill_type_builtin(static_cast<ast::BuiltinTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Array:
                fill_type_array(static_cast<ast::ArrayTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Path:
                fill_type_path(static_cast<ast::PathTypeExpr*>(t));
                break;
            case ast::TypeExprKind::Ref:
                fill_type_ref(static_cast<ast::RefTypeExpr*>(t));
                break;
            // case ast::TypeExprKind::Callable:
            //     fill_type_callable(static_cast<ast::CallableTypeExpr*>(t));
            //     break;
            default:
                assert(false && "fill_expr_type: unknown TypeExprKind");
                break;
            }
        }

        void fill_module(ast::Module* module)
        {
            auto mid = get_id(modules, module);
            auto& m = arena_.modules[mid];

            if (module->pathExpr_) m.package_path = get_id(exprs, module->pathExpr_);

            fill_id_vec(m.imports, module->imports, imports);
            fill_id_vec(m.decls, module->decls, decls);
        }

        void fill_import(ast::ImportDecl* imp)
        {
            auto id = get_id(imports, imp);
            auto& h = arena_.imports[id];

            if (imp->pathExpr_) h.path = get_id(exprs, imp->pathExpr_);
        }

        void fill_fndecl(ast::FunctionDecl* fn)
        {
            auto id = get_id(decls, fn);
            auto& d = arena_.decls[id];
            auto& f = std::get<FnDecl>(d.kind);

            fill_id_vec(d.tparams, fn->typeParamsDecls_, typeParams);
            fill_id_vec(f.params, fn->params_, params);

            if (fn->ret_) f.return_type = get_id(types, fn->ret_);
            if (fn->body_) f.body = get_id(blocks, fn->body_);
        }

        void fill_structdecl(ast::StructDecl* decl)
        {
            auto id = get_id(decls, decl);
            auto& d = arena_.decls[id];
            auto& s = std::get<StructDecl>(d.kind);

            fill_id_vec(d.tparams, decl->typeParamsDecls_, typeParams);
            fill_id_vec(s.fields, decl->fields_, fieldDecls);
        }

        // void fill_typealias(ast::TypeAliasDecl* decl)
        // {
        //     auto id = get_i);
        //     auto& d = arena_.decls[id];
        //     auto& ta = std::get<TypeAliasDecl>(d.kind);
        //
        //     fill_id_vec(d.tparams, dec
        //     if (decl->aliasedType_) ta.aliased = get_id(types, dec
        // }

        void fill_type_param(ast::TypeParamDecl*)
        {
        }

        void fill_param(ast::ParamDecl* param)
        {
            auto id = get_id(params, param);
            auto& p = arena_.params[id];
            if (param->type_) p.type = get_id(types, param->type_);
        }

        void fill_field_decl(ast::FieldDecl* field)
        {
            auto id = get_id(fieldDecls, field);
            auto& f = arena_.field_decls[id];
            if (field->type_) f.type = get_id(types, field->type_);
        }

        void fill_field_init(ast::FieldInitExpr* init)
        {
            auto id = get_id(fieldInits, init);
            auto& f = arena_.field_inits[id];
            if (init->value_) f.value = get_id(exprs, init->value_);
        }

        void fill_stmt_block(ast::BlockStatement* s)
        {
            const auto bid = get_id(blocks, s);
            auto& b = arena_.blocks[bid];
            fill_id_vec(b.stmts, s->statements_, stmts);

            const auto sid = get_id(stmts, s);
            auto& st = arena_.stmts[sid];
            auto& sb = std::get<StmtBlock>(st.kind);
            sb.block = bid; // redundant but safe
        }


        // ----- fill statements -----

        void fill_stmt_if(ast::IfStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& si = std::get<StmtIf>(st.kind);

            si.cond = get_id(exprs, s->condition_);
            si.then_blk = get_id(blocks, s->thenBody_);
            fill_id_vec(si.elseifs, s->elseIfs_, stmts);

            if (s->else_) si.else_ = get_id(stmts, s->else_);
        }

        void fill_stmt_elseif(ast::ElseIfStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& se = std::get<StmtElseIf>(st.kind);

            se.cond = get_id(exprs, s->condition_);
            se.blk = get_id(blocks, s->then_);
        }

        void fill_stmt_else(ast::ElseStatement* e)
        {
            auto id = get_id(stmts, e);
            auto& st = arena_.stmts[id];
            auto& se = std::get<StmtElse>(st.kind);

            se.blk = get_id(blocks, e->then_);
        }

        void fill_stmt_while(ast::WhileStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& sw = std::get<StmtWhile>(st.kind);

            sw.cond = get_id(exprs, s->condition_);
            sw.body = get_id(blocks, s->body_);
        }

        void fill_stmt_dowhile(ast::DoWhileStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& sd = std::get<StmtDoWhile>(st.kind);

            sd.body = get_id(blocks, s->body_);
            sd.cond = get_id(exprs, s->condition_);
        }

        void fill_stmt_break(ast::BreakStatement*)
        {
        }

        void fill_stmt_continue(ast::ContinueStatement*)
        {
        }

        void fill_stmt_return(ast::ReturnStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& sr = std::get<StmtReturn>(st.kind);

            if (s->expr_) sr.value = get_id(exprs, s->expr_);
        }

        void fill_stmt_var(ast::VarStmt* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& sv = std::get<StmtVar>(st.kind);

            if (s->type_) sv.type = get_id(types, s->type_);
            if (s->init_) sv.init = get_id(exprs, s->init_);
        }

        void fill_stmt_expr(ast::ExprStatement* s)
        {
            auto id = get_id(stmts, s);
            auto& st = arena_.stmts[id];
            auto& se = std::get<StmtExpr>(st.kind);

            se.expr = get_id(exprs, s->expr_);
        }

        // ----- fill expressions -----
        void fill_expr_path(ast::PathExpr*)
        {
        }

        void fill_expr_lit_int(ast::IntLiteralExpr* /*e*/)
        {
        }

        void fill_expr_lit_float(ast::FloatLiteralExpr* /*e*/)
        {
        }

        void fill_expr_lit_bool(ast::BoolLiteralExpr* /*e*/)
        {
        }

        void fill_expr_lit_char(ast::CharLiteralExpr* /*e*/)
        {
        }

        void fill_expr_lit_string(ast::StringLiteralExpr* /*e*/)
        {
        }

        void fill_expr_lit_array(ast::ArrayLiteralExpr* e)
        {
            const auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& arr = std::get<ExprLitArray>(ex.kind);

            fill_id_vec(arr.elements, e->v_, exprs);
        }

        void fill_expr_unary(ast::UnaryExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& eu = std::get<ExprUnary>(ex.kind);

            eu.rhs = get_id(exprs, e->expr_);
        }

        void fill_expr_binary(ast::BinaryExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& eb = std::get<ExprBinary>(ex.kind);

            eb.lhs = get_id(exprs, e->lhs_);
            eb.rhs = get_id(exprs, e->rhs_);
        }

        void fill_expr_assign(ast::AssignExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& ea = std::get<ExprAssign>(ex.kind);

            ea.lhs = get_id(exprs, e->lhs_);
            ea.rhs = get_id(exprs, e->rhs_);
        }

        void fill_expr_call(ast::CallExpr* e)
        {
            const auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& ec = std::get<ExprCall>(ex.kind);

            ec.callee = get_id(exprs, e->callee_);
            fill_id_vec(ec.targs, e->typeArgs_, types);
            fill_id_vec(ec.args, e->args_, exprs);
        }

        void fill_expr_index(ast::IndexExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& ei = std::get<ExprIndex>(ex.kind);

            ei.base = get_id(exprs, e->base_);
            ei.index = get_id(exprs, e->index_);
        }

        void fill_expr_field(ast::FieldExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& ef = std::get<ExprField>(ex.kind);

            ef.base = get_id(exprs, e->base_);
            ef.field = e->field;
        }

        void fill_expr_lit_struct(ast::StructLiteralExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& es = std::get<ExprLitStruct>(ex.kind);

            if (e->expr_) es.type = get_id(exprs, e->expr_);
            fill_id_vec(es.fields, e->elements_, fieldInits);
        }

        void fill_expr_cast(ast::CastExpr* e)
        {
            auto id = get_id(exprs, e);
            auto& ex = arena_.exprs[id];
            auto& ec = std::get<ExprCast>(ex.kind);

            ec.expr = get_id(exprs, e->source_);
            ec.type = get_id(types, e->targetSyntax_);
        }

        // ----- fill types -----
        void fill_type_builtin(ast::BuiltinTypeExpr* /*t*/)
        {
        }

        void fill_type_path(ast::PathTypeExpr* t)
        {
            auto id = get_id(types, t);
            auto& ty = arena_.types[id];
            auto& tp = std::get<TypePath>(ty.kind);

            if (t->pathExpr_) tp.path = get_id(exprs, t->pathExpr_);
            fill_id_vec(tp.targs, t->typeArgs_, types);
        }

        void fill_type_ref(ast::RefTypeExpr* t)
        {
            auto id = get_id(types, t);
            auto& ty = arena_.types[id];
            auto& tr = std::get<TypeRef>(ty.kind);

            tr.mut = t->mut_;
            tr.inner = get_id(types, t->pointee_);
        }

        void fill_type_array(ast::ArrayTypeExpr* t)
        {
            auto id = get_id(types, t);
            auto& ty = arena_.types[id];
            auto& ta = std::get<TypeArray>(ty.kind);

            ta.elem = get_id(types, t->type_);
            ta.size = get_id(exprs, t->sizeExpr_);
        }

        void lower()
        {
            for (auto& [module] : translation_.units)
            {
                stack.clear();

                defer_alloc(module);

                // -------- alloc phase --------
                for (size_t i = 0; i < stack.size(); ++i)
                {
                    ast::Node* node = stack[i];
                    switch (node->nodeType_)
                    {
#define X(Tag, NodeKindCase, AstPtrType, AllocFuncName, FillFuncName) \
case NodeKindCase: AllocFuncName(static_cast<AstPtrType>(node)); break;
#include "lower_x.def"
#undef X
                    default: break;
                    }
                }

                // -------- fill phase --------
                for (ast::Node* node : stack)
                {
                    switch (node->nodeType_)
                    {
#define X(Tag, NodeKindCase, AstPtrType, AllocFuncName, FillFuncName) \
case NodeKindCase: FillFuncName(static_cast<AstPtrType>(node)); break;
#include "lower_x.def"
#undef X
                    default: break;
                    }
                }
            }
        }
    };
}

#endif //INZ_LOWERER_HPP
