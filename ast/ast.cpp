#include "ast.hpp"


using namespace ast;

// ========= Expressions =========

IntLiteralExpr* Ast::mk_int_literal_expr(lex::SymId v, std::optional<kl::rt::IntKind> kind, const lex::Loc& loc)
{
    return make<IntLiteralExpr>(v, kind, loc);
}

BoolLiteralExpr* Ast::mk_bool_literal_expr(lex::SymId v, const lex::Loc& loc)
{
    return make<BoolLiteralExpr>(v, loc);
}

CharLiteralExpr* Ast::mk_char_literal_expr(kl::rt::character v, const lex::Loc& loc)
{
    return make<CharLiteralExpr>(v, loc);
}

ArrayLiteralExpr* Ast::mk_array_literal_expr(std::vector<ExprPtr>&& v, const lex::Loc& loc)
{
    return make<ArrayLiteralExpr>(std::move(v), loc);
}

StringLiteralExpr* Ast::mk_str_literal_expr(lex::SymId sym, const lex::Loc& loc)
{
    return make<StringLiteralExpr>(sym, loc);
}

FloatLiteralExpr* Ast::mk_float_literal_expr(lex::SymId v, std::optional<kl::rt::FloatKind> kind, const lex::Loc& loc)
{
    return make<FloatLiteralExpr>(v, kind, loc);
}


FieldInitExpr* Ast::mk_field_init_expr(lex::SymId name, ExprPtr value, const lex::Loc& loc)
{
    return make<FieldInitExpr>(name, value, loc);
}

PathExpr* Ast::mk_path_expr(std::vector<lex::SymId>&& path, const lex::Loc& loc)
{
    return make<PathExpr>(std::move(path), loc);
}

StructLiteralExpr* Ast::mk_struct_literal_expr(Expr* pathTypeExpr,
                                               std::vector<TypeExpr*>&& typeArgs,
                                               std::vector<FieldInitExpr*>&& elems,
                                               const lex::Loc& loc)
{
    return make<StructLiteralExpr>(pathTypeExpr, std::move(typeArgs), std::move(elems), loc);
}

PathTypeExpr* Ast::mk_path_type_expr(PathExpr* pathExpr, std::vector<TypeExpr*>&& typeArgs, const lex::Loc& loc)
{
    return make<PathTypeExpr>(pathExpr, std::move(typeArgs), loc);
}

ArrayTypeExpr* Ast::mk_array_type_expr(TypeExpr* typeExpr, ExprPtr sizeExpr, const lex::Loc& loc)
{
    return make<ArrayTypeExpr>(typeExpr, sizeExpr, loc);
}

RefTypeExpr* Ast::mk_ref_type_expr(TypeExpr* typeExpr, Mutability mutability, const lex::Loc& loc)
{
    return make<RefTypeExpr>(typeExpr, mutability, loc);
}

BuiltinTypeExpr* Ast::mk_builtin_type_expr(kl::rt::BuiltinTypeExprKind kind, const lex::Loc& loc)
{
    return make<BuiltinTypeExpr>(kind, loc);
}

UnaryExpr* Ast::mk_unary_op_expr(UnaryOp op, ExprPtr v, const lex::Loc& loc)
{
    return make<UnaryExpr>(op, v, loc);
}

BinaryExpr* Ast::mk_binary_op_expr(BinaryOp op, ExprPtr lhs, ExprPtr rhs, const lex::Loc& loc)
{
    return make<BinaryExpr>(op, lhs, rhs, loc);
}

AssignExpr* Ast::mk_assign_expr(ExprPtr lhs, ExprPtr rhs, AssignOp op, const lex::Loc& loc)
{
    return make<AssignExpr>(lhs, rhs, op, loc);
}

FieldExpr* Ast::mk_field_expr(ExprPtr base, const lex::SymId field, const lex::Loc& loc)
{
    return make<FieldExpr>(base, field, loc);
}

IndexExpr* Ast::mk_index(ExprPtr base, ExprPtr idx, const lex::Loc& loc)
{
    return make<IndexExpr>(base, idx, loc);
}

// ========= Statements =========

BlockStatement* Ast::mk_block_stmt(std::vector<StatementPtr>&& stmts, BlockKind kind, const lex::Loc& loc)
{
    return make<BlockStatement>(std::move(stmts), kind, loc);
}

ReturnStatement* Ast::mk_return_stmt(ExprPtr expr, const lex::Loc& loc)
{
    return make<ReturnStatement>(expr, loc);
}

ParamDecl* Ast::mk_param_decl(lex::SymId name, TypeExpr* typeExpr, const lex::Loc& loc)
{
    return make<ParamDecl>(name, typeExpr, loc);
}

VarStmt* Ast::mk_var_stmt(lex::SymId name, TypeExpr* tyExpr,
                          Mutability mutability, Storage storage,
                          Expr* init, const lex::Loc& loc)
{
    return make<VarStmt>(name, tyExpr, mutability, storage, init, loc);
}

IfStatement* Ast::mk_if_stmt(ExprPtr cond,
                             BlockStatement* thenStmt,
                             std::vector<ElseIfStatement*>&& elseIfs,
                             ElseStatement* elseStmt,
                             const lex::Loc& loc)
{
    return make<IfStatement>(cond, thenStmt, std::move(elseIfs), elseStmt, loc);
}

ElseIfStatement* Ast::mk_else_if_stmt(ExprPtr cond, BlockStatement* thenBlk, const lex::Loc& loc)
{
    return make<ElseIfStatement>(cond, thenBlk, loc);
}

ElseStatement* Ast::mk_else_stmt(BlockStatement* elseBlk, const lex::Loc& loc)
{
    return make<ElseStatement>(elseBlk, loc);
}


// ========= Declarations =========

FnDecl* Ast::mk_fn_decl(lex::SymId name,
                        std::vector<TypeParamDecl*>&& typeParamDecls,
                        std::vector<ParamDecl*>&& params,
                        TypeExpr* ret, BlockStatement* body,
                        bool isExported,
                        const lex::Loc& loc)
{
    return make<FnDecl>(name, std::move(typeParamDecls), std::move(params), ret, body, isExported, loc);
}

LoadFnDecl* Ast::mk_load_fn_decl(lex::SymId name,
                                 std::vector<ParamDecl*>&& params,
                                 TypeExpr* ret,
                                 bool isExported,
                                 const lex::Loc& loc)
{
    return make<LoadFnDecl>(name, std::move(params), ret, isExported, loc);
}

FieldDecl* Ast::mk_field_decl(lex::SymId name, TypeExpr* type, Visibility visibility, const lex::Loc& loc)
{
    return make<FieldDecl>(name, type, visibility, loc);
}

TypeParamDecl* Ast::mk_type_param_decl(lex::SymId name, const lex::Loc& loc)
{
    return make<TypeParamDecl>(name, loc);
}

StructDecl* Ast::mk_struct_decl(lex::SymId name, std::vector<TypeParamDecl*>&& typeParamDecls,
                                std::vector<FieldDecl*>&& fields, bool isExported, const lex::Loc& loc)
{
    return make<StructDecl>(name, std::move(typeParamDecls), std::move(fields), isExported, loc);
}

void Ast::mk_module(PathExpr* pathExpr, std::vector<ImportDecl*>&& imports,
                    std::vector<Decl*>&& decls, const lex::Loc& loc)
{
    module_ = make<Module>(pathExpr, std::move(imports), std::move(decls), loc);
}

ImportDecl* Ast::mk_import_decl(PathExpr* pathExpr, std::optional<lex::SymId> alias, bool is_public,
                                const lex::Loc& loc)
{
    return make<ImportDecl>(pathExpr, alias, is_public, loc);
}

RefExpr* Ast::mk_ref_expr(lex::SymId name, const lex::Loc& loc)
{
    return make<RefExpr>(name, loc);
}

ContinueStatement* Ast::mk_continue_stmt(const lex::Loc& loc)
{
    return make<ContinueStatement>(loc);
}

WhileStatement* Ast::mk_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc)
{
    return make<WhileStatement>(condition, body, loc);
}

DoWhileStatement* Ast::mk_do_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc)
{
    return make<DoWhileStatement>(condition, body, loc);
}

BreakStatement* Ast::mk_break_stmt(const lex::Loc& loc)
{
    return make<BreakStatement>(loc);
}

ExprStatement* Ast::mk_expr_stmt(ExprPtr expr, const lex::Loc& loc)
{
    return make<ExprStatement>(expr, loc);
}

CallExpr* Ast::mk_call_expr(ExprPtr callee,
                            std::vector<TypeExpr*>&& typeArgs,
                            std::vector<ExprPtr>&& args,
                            const lex::Loc& loc)
{
    return make<CallExpr>(callee, std::move(typeArgs), std::move(args), loc);
}
