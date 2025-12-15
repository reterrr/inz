#ifndef AST_AST_HPP
#define AST_AST_HPP

#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

#include <llvm/Support/Allocator.h>

#include "../generated/token.hpp" // lex::Loc, lex::SymId
#include "../types.hpp"           // kl_int, kl_double, kl_bool, ...

// Include base first
#include "nodes/expr/expr.hpp"
#include "nodes/stmt/statement.hpp"
#include "nodes/decl/decl.hpp"

// Include concrete nodes used by factory
#include "expr/builtin_type_expr.hpp"
#include "expr/ref_type_expr.hpp"
#include "nodes/project.hpp"
#include "nodes/expr/int_expr.hpp"
#include "nodes/expr/bool_expr.hpp"
#include "nodes/expr/string_expr.hpp"
#include "nodes/expr/float_expr.hpp"

#include "nodes/expr/field_init_expr.hpp"
#include "nodes/expr/obj_expr.hpp"
#include "nodes/expr/ref_expr.hpp"

#include "nodes/expr/unary_op_expression_kind.hpp"
#include "nodes/expr/unary_op_expr.hpp"
#include "nodes/expr/init_declarator_expr.hpp"

#include "nodes/expr/binary_op_exression_kind.hpp"
#include "nodes/expr/binary_op_expr.hpp"
#include "nodes/expr/assign_expr.hpp"

#include "nodes/expr/field_expr.hpp"

#include "nodes/expr/call_expr.hpp"
#include "nodes/expr/index_expr.hpp"


#include "nodes/stmt/block_statement.hpp"
#include "nodes/stmt/return_statement.hpp"
#include "nodes/stmt/if_statement.hpp"
#include "nodes/stmt/expr_statement.hpp"
#include "nodes/stmt/while_statement.hpp"
#include "nodes/stmt/continue_statement.hpp"
#include "nodes/stmt/break_statement.hpp"
#include "nodes/stmt/do_while_statement.hpp"


#include "nodes/decl/param_decl.hpp"
#include "nodes/decl/function_decl.hpp"
#include "nodes/decl/var_decl.hpp"
#include "nodes/decl/type_alias_decl.hpp"
#include "nodes/decl/struct_decl.hpp"
#include "nodes/decl/field_decl.hpp"

#include "nodes/module/import_decl.hpp"
#include "nodes/module/module.hpp"


#include "nodes/type/type.hpp"              // Type, CallableType
#include "nodes/expr/ref_expr.hpp"

#include "nodes/module/module.hpp"

#include "nodes/stmt/var_decl_statement.hpp"
#include "sema/type_interner.hpp"
#include "nodes/expr/array_type_expression.hpp"
#include "nodes/expr/path_type_expr.hpp"


namespace ast
{
    // ===== forward declarations (keep header light) =====
    struct Dtor final
    {
        void (*dtor)(void*);

        void* obj;

        void operator()() const noexcept
        {
            dtor(obj);
        }
    };

    // ====================================================

    class AST final
    {
        sema::type::TypeInterner type_interner_{};

        llvm::BumpPtrAllocator alloc_{};
        std::vector<Dtor> dtors_{};

        Project* project = nullptr;

        std::size_t expr_count_ = 0;
        std::size_t stmt_count_ = 0;
        std::size_t decl_count_ = 0;
        std::size_t module_count_ = 0;


        template <typename T, typename... Args>
        T* make(Args&&... args)
        {
            void* mem = alloc_.Allocate<T>();

            T* obj = ::new(mem) T(std::forward<Args>(args)...);

            if constexpr (std::is_base_of_v<Expr, T>) ++expr_count_;
            if constexpr (std::is_base_of_v<Statement, T>) ++stmt_count_;
            if constexpr (std::is_base_of_v<Decl, T>) ++decl_count_;
            if constexpr (std::is_base_of_v<Module, T>) ++module_count_;

            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                dtors_.push_back({
                    +[](void* o) { static_cast<T*>(o)->~T(); },
                    obj
                });
            }

            return obj;
        }

        void destroy_all()
        {
            std::for_each(dtors_.rbegin(), dtors_.rend(),
                          [](const Dtor& dtor) { dtor(); }
            );

            dtors_.clear();
            alloc_.Reset();
        }

    public:
        AST()
            : project(mk_project(std::vector<ModulePtr>{}, lex::Loc{}))
        {
        }

        ~AST()
        {
            destroy_all();
        }

        [[nodiscard]] Project* get_project() const { return project; }

        void project_add_module(ModulePtr module) const;

        Project* mk_project(std::vector<ModulePtr>&& modules, const lex::Loc& l);

        // ========= Expressions =========
        IntLiteralExpr* mk_int_literal_expr(kl_int v, const lex::Loc& loc);

        BoolLiteralExpr* mk_bool_literal_expr(kl_bool v, const lex::Loc& loc);

        StringLiteralExpr* mk_str_literal_expr(lex::SymId sym, const lex::Loc& loc);

        FloatLiteralExpr* mk_float_literal_expr(kl_float v, const lex::Loc& loc);

        // Field init for struct literals (return concrete pointer)
        FieldInitExpr* mk_field_init_expr(lex::SymId name, ExprPtr value, const lex::Loc& loc);

        // Object/struct literal
        PathLiteralExpr* mk_obj_literal_expr(PathTypeExpr* pathTypeExpr,
                                             std::vector<FieldInitExpr*>&& elems, const lex::Loc& loc);

        PathTypeExpr* mk_path_type_expr(std::vector<lex::SymId>&& segments, const lex::Loc& loc);
        ArrayTypeExpr* mk_array_type_expr(TypeExpr* typeExpr, ExprPtr sizeExpr, const lex::Loc& loc);
        RefTypeExpr* mk_ref_type_expr(TypeExpr* typeExpr, RefTypeExpr::Mutability mutability, const lex::Loc& loc);
        BuiltinTypeExpr* mk_builtin_type_expr(BuiltinTypeExpr::Kind kind, const lex::Loc& loc);

        // Unary / Binary ops
        UnaryExpr* mk_unary_op_expr(UnaryOp op, ExprPtr v, const lex::Loc& loc);

        BinaryExpr* mk_binary_op_expr(BinaryOp op, ExprPtr lhs, ExprPtr rhs, const lex::Loc& loc);

        AssignExpr* mk_assign_expr(ExprPtr lhs, ExprPtr rhs, AssignOp op, const lex::Loc& loc);

        FieldExpr* mk_field_expr(ExprPtr base, lex::SymId field, const lex::Loc& loc);


        IndexExpr* mk_index(ExprPtr base, ExprPtr idx, const lex::Loc& loc);

        // ========= Statements =========
        BlockStatement* mk_block_stmt(std::vector<StatementPtr>&& stmts, const lex::Loc& loc);

        ReturnStatement* mk_return_stmt(ExprPtr expr, const lex::Loc& loc);

        // if (cond) then;              // no else
        IfStatement* mk_if_stmt(ExprPtr cond, StatementPtr thenStmt, const lex::Loc& loc);

        ExprStatement* mk_expr_stmt(ExprPtr expr, const lex::Loc& loc);

        VarDeclStatement* mk_var_decl_stmt(VarDecl* decl, const lex::Loc& loc);

        ContinueStatement* mk_continue_stmt(const lex::Loc& loc);

        WhileStatement* mk_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc);

        DoWhileStatement* mk_do_while_stmt(ExprPtr condition, BlockStatement* body, const lex::Loc& loc);

        BreakStatement* mk_break_stmt(const lex::Loc& loc);


        // if (cond) then else other;   // with else
        //StatementPtr mk_if_stmt(ExprPtr cond, StatementPtr thenStmt, StatementPtr elseStmt, const lex::Loc &loc);

        ParamDecl* mk_param_decl(lex::SymId name, TypeExpr* typeExpr, const lex::Loc& loc);

        VarDecl* mk_var_decl(
            lex::SymId name,
            TypeExpr* tyExpr, VarDecl::Mutability mutability, const lex::Loc& loc);

        // ========= Declarations =========
        FunctionDecl* mk_fn_decl(lex::SymId name,
                                 std::vector<ParamDecl*>&& params,
                                 TypeExpr* ret,
                                 BlockStatement* body,
                                 // nullptr => prototype
                                 const lex::Loc& loc);

        FieldDecl* mk_field_decl(lex::SymId name, TypeExpr* type, FieldDecl::Visibility visibility,
                                 const lex::Loc& loc);

        StructDecl* mk_struct_decl(lex::SymId name, std::vector<FieldDecl*>&& fields, const lex::Loc& loc);

        Module* mk_module(std::vector<lex::SymId>&& package_path,
                          std::vector<ImportDecl*>&& imports,
                          std::vector<Decl*>&& decls,
                          const lex::Loc& loc);


        ImportDecl* mk_import_decl(std::vector<lex::SymId>&& path, std::optional<lex::SymId> alias, bool is_public,
                                   const lex::Loc& loc);


        RefExpr* mk_ref_expr(lex::SymId name, const lex::Loc& loc);

        CallExpr* mk_call_expr(ExprPtr callee, std::vector<ExprPtr>&& args, const lex::Loc& loc);

        // statements

        PathType* mk_type_path_single(lex::SymId segment, const lex::Loc& loc);

        PathType* mk_type_path_append(PathType* base, lex::SymId segment, const lex::Loc& loc);

        Type* mk_type_from_path(PathType* path, const lex::Loc& loc);


        // ======== Introspection (optional) ========
        [[nodiscard]] std::size_t expr_count() const noexcept { return expr_count_; }
        [[nodiscard]] std::size_t stmt_count() const noexcept { return stmt_count_; }
        [[nodiscard]] std::size_t decl_count() const noexcept { return decl_count_; }
        [[nodiscard]] std::size_t module_count() const noexcept { return module_count_; }
    };
} // namespace ast

#endif // AST_AST_HPP
