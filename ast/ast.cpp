#include "ast.hpp"


using namespace ast;

// ========= Expressions =========

void AST::project_add_module(ModulePtr module) const {
    project->modules.push_back(module);
}

Project *AST::mk_project(std::vector<ModulePtr> &&modules, const lex::Loc &l) {
    return make<Project>(std::move(modules), l);
}

IntLiteralExpr *AST::mk_int_literal_expr(kl_int v, const lex::Loc &loc) {
    return make<IntLiteralExpr>(v, loc);
}

BoolLiteralExpr *AST::mk_bool_literal_expr(kl_bool v, const lex::Loc &loc) {
    return make<BoolLiteralExpr>(v, loc);
}

StringLiteralExpr *AST::mk_str_literal_expr(lex::SymId sym, const lex::Loc &loc) {
    return make<StringLiteralExpr>(sym, loc);
}

FloatLiteralExpr *AST::mk_float_literal_expr(kl_float v, const lex::Loc &loc) {
    return make<FloatLiteralExpr>(v, loc);
}

FieldInitExpr *AST::mk_field_init_expr(lex::SymId name, ExprPtr value, const lex::Loc &loc) {
    return make<FieldInitExpr>(name, value, loc);
}

ObjLiteralExpr *AST::mk_obj_literal_expr(PathType *tyPath, std::vector<FieldInitExpr *> &&elems, const lex::Loc &loc) {
    return make<ObjLiteralExpr>(tyPath, std::move(elems), loc);
}

UnaryExpr *AST::mk_unary_op_expr(UnaryOp op, ExprPtr v, const lex::Loc &loc) {
    return make<UnaryExpr>(op, v, loc);
}

BinaryExpr *AST::mk_binary_op_expr(BinaryOp op, ExprPtr lhs, ExprPtr rhs, const lex::Loc &loc) {
    return make<BinaryExpr>(op, lhs, rhs, loc);
}

AssignExpr *AST::mk_assign_expr(ExprPtr lhs, ExprPtr rhs, AssignOp op, const lex::Loc &loc) {
    return make<AssignExpr>(lhs, rhs, op, loc);
}

FieldExpr *AST::mk_field_expr(ExprPtr base, const lex::SymId field, const lex::Loc &loc) {
    return make<FieldExpr>(base, field, loc);
}

InitDeclarator *AST::mk_var_declarator_expr(const lex::SymId name, ExprPtr init, const lex::Loc &loc) {
    return make<InitDeclarator>(name, init, loc);
}

IndexExpr *AST::mk_index(ExprPtr base, ExprPtr idx, const lex::Loc &loc) {
    return make<IndexExpr>(base, idx, loc);
}

// ========= Statements =========

BlockStatement *AST::mk_block_stmt(std::vector<StatementPtr> &&stmts, const lex::Loc &loc) {
    return make<BlockStatement>(std::move(stmts), loc);
}

ReturnStatement *AST::mk_return_stmt(ExprPtr expr, const lex::Loc &loc) {
    return make<ReturnStatement>(expr, loc);
}

IfStatement *AST::mk_if_stmt(ExprPtr cond, StatementPtr thenStmt, const lex::Loc &loc) {
    // If your IfStatement takes an optional else, pass nullptr
    return make<IfStatement>(cond, thenStmt, /*else*/ loc);
}

ParamDecl *AST::mk_param_decl(lex::SymId name, Type *type, TypeSpecifier q, const lex::Loc &loc) {
    return make<ParamDecl>(name, type, q, loc);
}

VarDecl *AST::mk_var_decl(std::vector<InitDeclarator *> &&decls, Type *ty, TypeSpecifier spec, TypeRegion reg,
                          const lex::Loc &loc) {
    return make<VarDecl>(std::move(decls), ty, spec, reg, loc);
}

// StatementPtr AST::mk_if_stmt(ExprPtr cond, StatementPtr thenStmt, StatementPtr elseStmt, const lex::Loc& loc) {
//     return make<IfStatement>(cond, thenStmt, elseStmt, loc);
// }

// ========= Declarations =========

FunctionDecl *AST::mk_fn_decl(lex::SymId name,
                              CallableType *type,
                              std::vector<ParamDecl *> &&params,
                              Type *ret,
                              BlockStatement *body,
                              const lex::Loc &loc) {
    return make<FunctionDecl>(name, type, std::move(params), ret, body, loc);
}

FieldDecl *AST::mk_field_decl(lex::SymId name, Type *type, TypeSpecifier spec, bool is_public, const lex::Loc &loc) {
    return make<FieldDecl>(name, type, spec, is_public, loc);
}

StructDecl *AST::mk_struct_decl(lex::SymId name, std::vector<FieldDecl *> &&fields, const lex::Loc &loc) {
    return make<StructDecl>(name, std::move(fields), loc);
}

Module *AST::mk_module(std::vector<lex::SymId> &&package_path, std::vector<ImportDecl *> &&imports,
                       std::vector<Decl *> &&decls, const lex::Loc &loc) {
    return make<Module>(std::move(package_path), std::move(imports), std::move(decls), loc);
}

ImportDecl *AST::mk_import_decl(std::vector<lex::SymId> &&path, std::optional<lex::SymId> alias, bool is_public,
                                const lex::Loc &loc) {
    return make<ImportDecl>(std::move(path), alias, is_public, loc);
}

RefExpr *AST::mk_ref_expr(lex::SymId name, const lex::Loc &loc) {
    return make<RefExpr>(name, loc);
}

VarDeclStatement *AST::mk_var_decl_stmt(std::vector<InitDeclarator *> &&declarators,
                                        Type *type,
                                        TypeSpecifier specifier,
                                        TypeRegion region,
                                        const lex::Loc &loc) {
    return make<VarDeclStatement>(std::move(declarators), type, loc, specifier, region);
}

ContinueStatement *AST::mk_continue_stmt(const lex::Loc &loc) {
    return make<ContinueStatement>(loc);
}

WhileStatement *AST::mk_while_stmt(ExprPtr condition, BlockStatement *body, const lex::Loc &loc) {
    return make<WhileStatement>(condition, body, loc);
}

DoWhileStatement *AST::mk_do_while_stmt(ExprPtr condition, BlockStatement *body, const lex::Loc &loc) {
    return make<DoWhileStatement>(condition, body, loc);
}

BreakStatement *AST::mk_break_stmt(const lex::Loc &loc) {
    return make<BreakStatement>(loc);
}

ExprStatement *AST::mk_expr_stmt(ExprPtr expr, const lex::Loc &loc) {
    return make<ExprStatement>(expr, loc);
}

CallExpr *AST::mk_call_expr(ExprPtr callee, std::vector<ExprPtr> &&args, const lex::Loc &loc) {
    return make<CallExpr>(callee, std::move(args), loc);
}

CallableType *AST::mk_callable_type(std::vector<Type *> &&param_types, Type *ret, const lex::Loc &loc) {
    return make<CallableType>(std::move(param_types), ret, loc);
}

BuiltinType *AST::mk_builtin_type(ast::BuiltinTy type, const lex::Loc &loc) {
    return make<BuiltinType>(type, loc);
}

FixedArrayType *AST::mk_fixed_array_type(Type *type, std::uint64_t length, const lex::Loc &loc) {
    return make<FixedArrayType>(type, length, loc);
}

PathType *AST::mk_type_path_single(lex::SymId segment, const lex::Loc &loc) {
    std::vector<lex::SymId> segs;
    segs.push_back(segment);
    return make<PathType>(std::move(segs), loc);
}

PathType *AST::mk_type_path_append(PathType *base, lex::SymId segment, const lex::Loc &loc) {
    // extend the existing path in-place
    base->segments.push_back(segment);
    base->loc = loc; // keep full span (e.g., for "foo.bar")
    return base;
}

Type *AST::mk_type_from_path(PathType *path, const lex::Loc &loc) {
    // PathType already derives from Type; just update location and return it as Type*
    path->loc = loc;
    return path;
}
