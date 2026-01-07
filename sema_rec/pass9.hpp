#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "translation.hpp"
#include "ast/nodes/visit/overallvisitor.hpp"

// AST roots

// Decls/Stmts/Exprs used

#include "expr/ref_expr.hpp"
#include "expr/char_literal_expr.hpp"

// Passes
#include "pass2.hpp"
#include "pass4.hpp"
#include "pass_4.5.hpp"
#include "pass6.hpp"
#include "pass7.hpp"
#include "pass8.hpp"

// LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

namespace sema
{
    // ---------------- Diagnostics ----------------

    struct Pass9Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            UnknownFunctionId,
            InvalidCallee,
            RefNotCallable,
            UnsupportedExpr,
            UnsupportedStmt,
            MissingBinding,
            AssignToNonLocal,
            ReturnTypeMismatch,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    // ---------------- Runtime ABI config ----------------
    // You can rename these runtime entrypoints later; Pass 9 only depends on this table.

    struct RuntimeAbi final
    {
        // Object pointer type: i8*
        // Boxing
        std::string rt_int_u64 = "rt_int_u64";     // (i64) -> Obj*
        std::string rt_float_f64 = "rt_float_f64"; // (double) -> Obj*

        // Arithmetic (Obj*, Obj*) -> Obj*
        std::string rt_add = "rt_add";
        std::string rt_sub = "rt_sub";
        std::string rt_mul = "rt_mul";
        std::string rt_div = "rt_div";
        std::string rt_mod = "rt_mod";

        // Comparisons (Obj*, Obj*) -> i1
        std::string rt_eq = "rt_eq";
        std::string rt_ne = "rt_ne";
        std::string rt_lt = "rt_lt";
        std::string rt_le = "rt_le";
        std::string rt_gt = "rt_gt";
        std::string rt_ge = "rt_ge";

        // Optional numeric unary
        std::string rt_neg = "rt_neg"; // (Obj*) -> Obj*
    };

    // ---------------- Result ----------------

    struct Pass9Result final
    {
        std::unique_ptr<llvm::Module> module;

        // for debugging / later passes
        std::unordered_map<FnId, llvm::Function*, LocalIdHash<FnTag>> llvm_fn_by_id;

        std::vector<Pass9Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    // ---------------- Codegen Visitor ----------------

    class Pass9CodegenVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass9CodegenVisitor(const Pass2Result& p2,
                            const Pass4Result& p4,
                            const Pass4_5Result& p45,
                            const Pass6Result& p6,
                            const Pass7Result& p7,
                            const Pass8Result& p8,
                            const RuntimeAbi& abi,
                            Pass9Result& out,
                            llvm::LLVMContext& llctx,
                            llvm::Module& llmod,
                            std::uint32_t unit_index);

        // Module entry
        void visit(ast::Module& m) override;

        // Decl
        void visit(ast::FnDecl& f) override;
        void visit(ast::ParamDecl& p) override;

        // Stmt
        void visit(ast::BlockStatement& b) override;
        void visit(ast::VarStmt& v) override;
        void visit(ast::ExprStatement& e) override;
        void visit(ast::ReturnStatement& r) override;
        void visit(ast::IfStatement& i) override;
        void visit(ast::WhileStatement& w) override;
        void visit(ast::DoWhileStatement& d) override;

        void visit(ast::BreakStatement& b) override;
        void visit(ast::ContinueStatement& c) override;

        // Expr
        void visit(ast::BoolLiteralExpr& b) override;
        void visit(ast::IntLiteralExpr& i) override;
        void visit(ast::FloatLiteralExpr& f) override;
        void visit(ast::CharLiteralExpr& c) override;
        void visit(ast::StringLiteralExpr& s) override;

        void visit(ast::RefExpr& r) override;
        void visit(ast::AssignExpr& a) override;
        void visit(ast::UnaryExpr& u) override;
        void visit(ast::BinaryExpr& b) override;
        void visit(ast::CallExpr& c) override;
        void visit(ast::PathExpr& p) override;

    private:
        // Inputs
        const Pass2Result& p2_;
        const Pass4Result& p4_;
        const Pass4_5Result& p45_;
        const Pass6Result& p6_;
        const Pass7Result& p7_;
        const Pass8Result& p8_;
        const RuntimeAbi& abi_;
        Pass9Result& out_;

        // LLVM
        llvm::LLVMContext& llctx_;
        llvm::Module& llmod_;
        llvm::IRBuilder<> bld_;

        // Current unit/env
        std::uint32_t unit_index_ = 0;
        const ModuleVisibleEnv* env_ = nullptr;

        // Current function context
        const FnBindings* cur_fn_bind_ = nullptr;
        llvm::Function* cur_llfn_ = nullptr;
        llvm::BasicBlock* cur_entry_ = nullptr;
        std::vector<llvm::AllocaInst*> slot_allocas_;

        // Loop control targets
        struct LoopTargets
        {
            llvm::BasicBlock* break_bb = nullptr;
            llvm::BasicBlock* cont_bb = nullptr;
        };
        std::vector<LoopTargets> loop_stack_;

        // Expression result (either i1 or Obj*)
        llvm::Value* last_v_ = nullptr;

        // Types
        llvm::Type* ty_void() const;
        llvm::IntegerType* ty_i1() const;
        llvm::IntegerType* ty_i64() const;
        llvm::Type* ty_f64() const;
        llvm::PointerType* ty_objp() const;

        // Helpers
        void push_diag(Pass9Diagnostic::Code c, const lex::Loc& loc, std::string msg) const;

        static std::string sanitize_key(std::string s);
        static std::string mangle_fn_name(const Pass2Result& p2, FnId id, lex::SymId name);

        llvm::Function* get_or_declare_runtime(std::string_view name,
                                               llvm::FunctionType* fty);

    public: llvm::Function* get_or_create_user_fn(FnId id, ast::FnDecl* decl, std::uint32_t decl_unit) const;

        bool fn_returns_void(const ast::FnDecl& f) const;

        // Resolve FnId -> decl + unit index
        ast::FnDecl* fn_decl_from_id(FnId id, std::uint32_t& out_unit) const;

        // Expression codegen entry with tag
        DynTag tag_of(ast::Expr* e) const;
        llvm::Value* emit_expr(ast::Expr* e); // returns i1 or Obj* depending on Pass 8

        // Conversions / runtime boxing
        llvm::Value* emit_box_int_u64(std::uint64_t v);
        llvm::Value* emit_box_float_f64(double v);

        // RefExpr binding
        std::optional<Binding> get_binding(const ast::RefExpr& r) const;

        // Call target resolution
        llvm::Function* resolve_callee(ast::Expr* callee_expr, const lex::Loc& loc);

        // Binary short-circuit
        llvm::Value* emit_logical_and(ast::Expr* lhs, ast::Expr* rhs, const lex::Loc& loc);
        llvm::Value* emit_logical_or(ast::Expr* lhs, ast::Expr* rhs, const lex::Loc& loc);

        // Ensure current insertion is valid
        bool is_terminated() const;
    };

    // Driver: builds one LLVM module containing all user functions, then emits bodies.
    Pass9Result run_pass9_codegen(const Translation& tr,
                                  const Pass2Result& p2,
                                  const Pass4Result& p4,
                                  const Pass4_5Result& p45,
                                  const Pass6Result& p6,
                                  const Pass7Result& p7,
                                  const Pass8Result& p8,
                                  llvm::LLVMContext& llctx,
                                  const RuntimeAbi& abi = {});
} // namespace sema
