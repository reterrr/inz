#include "ast.hpp"


using namespace ast;

// ========= Expressions =========

void AST::project_add_module(ModulePtr module) const
{
    project->modules.push_back(module);
}

Project* AST::mk_project(std::vector<ModulePtr>&& modules, const lex::Loc& l)
{
    return make<Project>(std::move(modules), l);
}

IntLiteralExpr* AST::mk_int_literal_expr(lex::SymId v, std::optional<kl::rt::IntKind> kind, const lex::Loc& loc)
{
    return make<IntLiteralExpr>(v, kind, loc);
}

BoolLiteralExpr* AST::mk_bool_literal_expr(lex::SymId v, const lex::Loc& loc)
{
    return make<BoolLiteralExpr>(v, loc);
}

CharLiteralExpr* AST::mk_char_literal_expr(kl::rt::character v, const lex::Loc& loc)
{
    return make<CharLiteralExpr>(v, loc);
}

ArrayLiteralExpr* AST::mk_array_literal_expr(std::vector<ExprPtr>&& v, const lex::Loc& loc)
{
    return make<ArrayLiteralExpr>(std::move(v), loc);
}

StringLiteralExpr* AST::mk_str_literal_expr(lex::SymId sym, const lex::Loc& loc)
{
    return make<StringLiteralExpr>(sym, loc);
}

FloatLiteralExpr* AST::mk_float_literal_expr(lex::SymId v, std::optional<kl::rt::FloatKind> kind, const lex::Loc& loc)
{
    return make<FloatLiteralExpr>(v, kind, loc);
}

FieldInitExpr* AST::mk_field_init_expr(lex::SymId name, ExprPtr value, const lex::Loc& loc)
{
    return make<FieldInitExpr>(name, value, loc);
}

PathExpr* AST::mk_path_expr(std::vector<lex::SymId>&& path, const lex::Loc& loc)
{
    return make<PathExpr>(std::move(path), loc);
}

StructLiteralExpr* AST::mk_struct_literal_expr(Expr* pathTypeExpr,
                                               std::vector<TypeExpr*>&& typeArgs,
                                               std::vector<FieldInitExpr*>&& elems,
                                               const lex::Loc& loc)
{
    return make<StructLiteralExpr>(pathTypeExpr, std::move(typeArgs), std::move(elems), loc);
}

PathTypeExpr* AST::mk_path_type_expr(PathExpr* pathExpr, std::vector<TypeExpr*>&& typeArgs, const lex::Loc& loc)
{
    return make<PathTypeExpr>(pathExpr, std::move(typeArgs), loc);
}

ArrayTypeExpr* AST::mk_array_type_expr(TypeExpr* typeExpr, ExprPtr sizeExpr, const lex::Loc& loc)
{
    return make<ArrayTypeExpr>(typeExpr, sizeExpr, loc);
}

RefTypeExpr* AST::mk_ref_type_expr(TypeExpr* typeExpr, RefTypeExpr::Mutability mutability, const lex::Loc& loc)
{
    return make<RefTypeExpr>(typeExpr, mutability, loc);
}

BuiltinTypeExpr* AST::mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind kind, const lex::Loc& loc)
{
    return make<BuiltinTypeExpr>(kind, loc);
}

UnaryExpr* AST::mk_unary_op_expr(UnaryOp op, ExprPtr v, const lex::Loc& loc)
{
    return make<UnaryExpr>(op, v, loc);
}

BinaryExpr* AST::mk_binary_op_expr(BinaryOp op, ExprPtr lhs, ExprPtr rhs, const lex::Loc& loc)
{
    return make<BinaryExpr>(op, lhs, rhs, loc);
}

AssignExpr* AST::mk_assign_expr(ExprPtr lhs, ExprPtr rhs, AssignOp op, const lex::Loc& loc)
{
    return make<AssignExpr>(lhs, rhs, op, loc);
}

FieldExpr* AST::mk_field_expr(ExprPtr base, const lex::SymId field, const lex::Loc& loc)
{
    return make<FieldExpr>(base, field, loc);
}

IndexExpr* AST::mk_index(ExprPtr base, ExprPtr idx, const lex::Loc& loc)
{
    return make<IndexExpr>(base, idx, loc);
}

// ========= Statements =========

BlockStatement* AST::mk_block_stmt(std::vector<StatementPtr>&& stmts, const lex::Loc& loc)
{
    return make<BlockStatement>(std::move(stmts), loc);
}

ReturnStatement* AST::mk_return_stmt(ExprPtr expr, const lex::Loc& loc)
{
    return make<ReturnStatement>(expr, loc);
}

ParamDecl* AST::mk_param_decl(lex::SymId name, TypeExpr* typeExpr, const lex::Loc& loc)
{
    return make<ParamDecl>(name, typeExpr, loc);
}

VarDecl* AST::mk_var_decl(lex::SymId name, TypeExpr* tyExpr,
                          VarDecl::Mutability mutability, Expr* init, const lex::Loc& loc)
{
    return make<VarDecl>(name, tyExpr, mutability, init, loc);
}

IfStatement* AST::mk_if_stmt(ExprPtr cond,
                             BlockStatement* thenStmt,
                             std::vector<ElseIfStatement*>&& elseIfs,
                             ElseStatement* elseStmt,
                             const lex::Loc& loc)
{
    return make<IfStatement>(cond, thenStmt, std::move(elseIfs), elseStmt, loc);
}

ElseIfStatement* AST::mk_else_if_stmt(ExprPtr cond, BlockStatement* thenBlk, const lex::Loc& loc)
{
    return make<ElseIfStatement>(cond, thenBlk, loc);
}

ElseStatement* AST::mk_else_stmt(BlockStatement* elseBlk, const lex::Loc& loc)
{
    return make<ElseStatement>(elseBlk, loc);
}

// ========= Declarations =========

FunctionDecl* AST::mk_fn_decl(lex::SymId name,
                              std::vector<TypeParamDecl*>&& typeParamDecls,
                              std::vector<ParamDecl*>&& params,
                              TypeExpr* ret, BlockStatement* body,
                              const lex::Loc& loc)
{
    return make<FunctionDecl>(name, std::move(typeParamDecls), std::move(params), ret, body, loc);
}

FieldDecl* AST::mk_field_decl(lex::SymId name, TypeExpr* type, FieldDecl::Visibility visibility, const lex::Loc& loc)
{
    return make<FieldDecl>(name, type, visibility, loc);
}

TypeParamDecl* AST::mk_type_param_decl(lex::SymId name, const lex::Loc& loc)
{
    return make<TypeParamDecl>(name, loc);
}

StructDecl* AST::mk_struct_decl(lex::SymId name, std::vector<TypeParamDecl*>&& typeParamDecls,
                                std::vector<FieldDecl*>&& fields, const lex::Loc& loc)
{
    return make<StructDecl>(name, std::move(typeParamDecls), std::move(fields), loc);
}

Module* AST::mk_module(std::vector<lex::SymId>&& package_path, std::vector<ImportDecl*>&& imports,
                       std::vector<Decl*>&& decls, const lex::Loc& loc)
{
    return make<Module>(std::move(package_path), std::move(imports), std::move(decls), loc);
}

ImportDecl* AST::mk_import_decl(std::vector<lex::SymId>&& path, std::optional<lex::SymId> alias, bool is_public,
                                const lex::Loc& loc)
{
    return make<ImportDecl>(std::move(path), alias, is_public, loc);
}

RefExpr* AST::mk_ref_expr(lex::SymId name, const lex::Loc& loc)
{
    return make<RefExpr>(name, loc);
}

ContinueStatement* AST::mk_continue_stmt(const lex::Loc& loc)
{
    return make<ContinueStatement>(loc);
}

WhileStatement* AST::mk_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc)
{
    return make<WhileStatement>(condition, body, loc);
}

DoWhileStatement* AST::mk_do_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc)
{
    return make<DoWhileStatement>(condition, body, loc);
}

BreakStatement* AST::mk_break_stmt(const lex::Loc& loc)
{
    return make<BreakStatement>(loc);
}

ExprStatement* AST::mk_expr_stmt(ExprPtr expr, const lex::Loc& loc)
{
    return make<ExprStatement>(expr, loc);
}

VarDeclStatement* AST::mk_var_decl_stmt(VarDecl* decl, const lex::Loc& loc)
{
    return make<VarDeclStatement>(decl, loc);
}

CallExpr* AST::mk_call_expr(ExprPtr callee,
                            std::vector<TypeExpr*>&& typeArgs,
                            std::vector<ExprPtr>&& args,
                            const lex::Loc& loc)
{
    return make<CallExpr>(callee, std::move(typeArgs), std::move(args), loc);
}
