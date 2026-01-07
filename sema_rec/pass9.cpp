#include "pass9.hpp"

#include <cassert>
#include <sstream>

namespace sema
{
    // ---------------- Types ----------------

    llvm::Type* Pass9CodegenVisitor::ty_void() const { return llvm::Type::getVoidTy(llctx_); }
    llvm::IntegerType* Pass9CodegenVisitor::ty_i1() const { return llvm::Type::getInt1Ty(llctx_); }
    llvm::IntegerType* Pass9CodegenVisitor::ty_i64() const { return llvm::Type::getInt64Ty(llctx_); }
    llvm::Type* Pass9CodegenVisitor::ty_f64() const { return llvm::Type::getDoubleTy(llctx_); }
    llvm::PointerType* Pass9CodegenVisitor::ty_objp() const { return llvm::PointerType::get(llctx_, 0); }

    // ---------------- Ctor ----------------

    Pass9CodegenVisitor::Pass9CodegenVisitor(const Pass2Result& p2,
                                             const Pass4Result& p4,
                                             const Pass4_5Result& p45,
                                             const Pass6Result& p6,
                                             const Pass7Result& p7,
                                             const Pass8Result& p8,
                                             const RuntimeAbi& abi,
                                             Pass9Result& out,
                                             llvm::LLVMContext& llctx,
                                             llvm::Module& llmod,
                                             std::uint32_t unit_index)
        : p2_(p2)
          , p4_(p4)
          , p45_(p45)
          , p6_(p6)
          , p7_(p7)
          , p8_(p8)
          , abi_(abi)
          , out_(out)
          , llctx_(llctx)
          , llmod_(llmod)
          , bld_(llctx)
          , unit_index_(unit_index)
    {
    }

    // ---------------- Diagnostics ----------------

    void Pass9CodegenVisitor::push_diag(Pass9Diagnostic::Code c, const lex::Loc& loc, std::string msg) const
    {
        out_.diagnostics.push_back(Pass9Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    // ---------------- Name mangling ----------------

    std::string Pass9CodegenVisitor::sanitize_key(std::string s)
    {
        for (char& c : s)
        {
            if (c == ':' || c == '/' || c == '\\' || c == '.' || c == '-' || c == ' ')
                c = '_';
        }
        return s;
    }

    std::string Pass9CodegenVisitor::mangle_fn_name(const Pass2Result& p2, FnId id, lex::SymId name)
    {
        // Use module key if available; fallback to module numeric id
        std::string mod_key = "mod_" + std::to_string(id.module.value);

        if (id.module.value < p2.modules.size())
            mod_key = sanitize_key(p2.modules[id.module.value].key);

        std::ostringstream oss;
        oss << "kl__" << mod_key << "__fn__" << static_cast<std::uint32_t>(name)
            << "__" << id.index;
        return oss.str();
    }

    // ---------------- Runtime declarations ----------------

    llvm::Function* Pass9CodegenVisitor::get_or_declare_runtime(std::string_view name,
                                                                llvm::FunctionType* fty)
    {
        if (auto* f = llmod_.getFunction(std::string(name)))
            return f;

        auto* fn = llvm::Function::Create(fty,
                                          llvm::Function::ExternalLinkage,
                                          std::string(name),
                                          llmod_);
        fn->setCallingConv(llvm::CallingConv::C);
        return fn;
    }

    // ---------------- Pass 4 lookup ----------------

    ast::FnDecl* Pass9CodegenVisitor::fn_decl_from_id(FnId id, std::uint32_t& out_unit) const
    {
        // ModuleId -> unit index via Pass2
        if (id.module.value >= p2_.modules.size())
            return nullptr;

        out_unit = p2_.modules[id.module.value].unit_index;
        if (out_unit >= p4_.modules.size())
            return nullptr;

        const ModuleGlobals& mg = p4_.modules[out_unit];

        // id.index is local fn index inside that module
        if (id.index >= mg.fns.size())
            return nullptr;

        return mg.fns[id.index].decl;
    }

    bool Pass9CodegenVisitor::fn_returns_void(const ast::FnDecl& f) const
    {
        // Minimal dynamic policy:
        // Return type void if it is BuiltinTypeExpr(Void).
        // Adapt if your AST supports other void forms.
        if (!f.ret_) return true;

        if (auto* bt = dynamic_cast<ast::BuiltinTypeExpr*>(f.ret_))
        {
            return bt->kind_ == kl::rt::BuiltinTypeExprKind::Void;
        }

        return false;
    }

    llvm::Function* Pass9CodegenVisitor::get_or_create_user_fn(FnId id, ast::FnDecl* decl,
                                                               std::uint32_t decl_unit) const
    {
        auto it = out_.llvm_fn_by_id.find(id);
        if (it != out_.llvm_fn_by_id.end())
            return it->second;

        if (!decl)
        {
            push_diag(Pass9Diagnostic::Code::UnknownFunctionId, lex::Loc{}, "unknown function id in codegen");
            return nullptr;
        }

        // Function signature: all params are Obj*, return is Obj* or void.
        std::vector<llvm::Type*> param_tys;
        param_tys.reserve(decl->params_.size());

        for (auto* p : decl->params_)
        {
            (void)p;
            param_tys.push_back(ty_objp());
        }

        llvm::Type* ret_ty = fn_returns_void(*decl) ? ty_void() : static_cast<llvm::Type*>(ty_objp());

        auto* fty = llvm::FunctionType::get(ret_ty, param_tys, false);

        const std::string mangled = mangle_fn_name(p2_, id, decl->name_);
        auto* llfn = llvm::Function::Create(fty,
                                            llvm::Function::ExternalLinkage,
                                            mangled,
                                            llmod_);

        // Give args stable names (for debugging)
        std::size_t i = 0;
        for (auto& arg : llfn->args())
        {
            arg.setName("arg" + std::to_string(i++));
        }

        out_.llvm_fn_by_id.emplace(id, llfn);
        return llfn;
    }

    // ---------------- Pass 8 tag lookup ----------------

    DynTag Pass9CodegenVisitor::tag_of(ast::Expr* e) const
    {
        if (!e) return DynTag::void_();
        if (auto it = p8_.tag_of.find(e); it != p8_.tag_of.end())
            return it->second;
        // If missing, assume Obj (keeps codegen moving)
        return DynTag::obj();
    }

    // ---------------- Boxing literals ----------------

    llvm::Value* Pass9CodegenVisitor::emit_box_int_u64(std::uint64_t v)
    {
        auto* fty = llvm::FunctionType::get(ty_objp(), {ty_i64()}, false);
        auto* fn = get_or_declare_runtime(abi_.rt_int_u64, fty);
        auto* arg = llvm::ConstantInt::get(ty_i64(), static_cast<std::uint64_t>(v), false);
        return bld_.CreateCall(fn, {arg}, "intobj");
    }

    llvm::Value* Pass9CodegenVisitor::emit_box_float_f64(double v)
    {
        auto* fty = llvm::FunctionType::get(ty_objp(), {ty_f64()}, false);
        auto* fn = get_or_declare_runtime(abi_.rt_float_f64, fty);
        auto* arg = llvm::ConstantFP::get(ty_f64(), v);
        return bld_.CreateCall(fn, {arg}, "fltobj");
    }

    // ---------------- Bindings ----------------

    std::optional<Binding> Pass9CodegenVisitor::get_binding(const ast::RefExpr& r) const
    {
        if (!cur_fn_bind_) return std::nullopt;

        auto it = cur_fn_bind_->ref_binding.find(&r);
        if (it == cur_fn_bind_->ref_binding.end())
            return std::nullopt;

        return it->second;
    }

    // ---------------- Control-flow state ----------------

    bool Pass9CodegenVisitor::is_terminated() const
    {
        if (!bld_.GetInsertBlock()) return true;
        return bld_.GetInsertBlock()->getTerminator() != nullptr;
    }

    // ---------------- Callee resolution ----------------

    llvm::Function* Pass9CodegenVisitor::resolve_callee(ast::Expr* callee_expr, const lex::Loc& loc)
    {
        if (!callee_expr) return nullptr;

        // Most common: callee is RefExpr bound to GlobalFn
        if (auto* r = dynamic_cast<ast::RefExpr*>(callee_expr))
        {
            auto b = get_binding(*r);
            if (!b.has_value())
            {
                push_diag(Pass9Diagnostic::Code::MissingBinding, loc, "missing binding for callee ref");
                return nullptr;
            }

            if (b->kind == BindingKind::GlobalFn)
            {
                std::uint32_t decl_unit = 0;
                ast::FnDecl* decl = fn_decl_from_id(b->fn, decl_unit);
                return get_or_create_user_fn(b->fn, decl, decl_unit);
            }

            push_diag(Pass9Diagnostic::Code::RefNotCallable, loc, "callee ref is not a global function");
            return nullptr;
        }

        // Qualified call: PathExpr alias::name
        if (auto* p = dynamic_cast<ast::PathExpr*>(callee_expr))
        {
            if (!env_)
            {
                push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "no module env for qualified call");
                return nullptr;
            }

            const auto& segs = p->path_;
            if (segs.size() == 1)
            {
                // Treat as unqualified function name: attempt visible_fns
                auto it = env_->visible_fns.find(segs[0]);
                if (it == env_->visible_fns.end())
                {
                    push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "unknown function name in call");
                    return nullptr;
                }

                const FnId id = it->second;
                std::uint32_t decl_unit = 0;
                ast::FnDecl* decl = fn_decl_from_id(id, decl_unit);
                return get_or_create_user_fn(id, decl, decl_unit);
            }

            if (segs.size() == 2)
            {
                // alias::name : resolve in env imports
                const lex::SymId alias = segs[0];
                const lex::SymId name = segs[1];

                auto itImp = env_->imports_by_alias.find(alias);
                if (itImp == env_->imports_by_alias.end() || !itImp->second.target_globals)
                {
                    push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "unknown import alias in qualified call");
                    return nullptr;
                }

                const ModuleGlobals& imported = *itImp->second.target_globals;

                // imported.fn_by_name is public-only (by your design)
                auto itFn = imported.fn_by_name.find(name);
                if (itFn == imported.fn_by_name.end())
                {
                    push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "unknown function name in qualified call");
                    return nullptr;
                }

                const FnId id = itFn->second;
                std::uint32_t decl_unit = 0;
                ast::FnDecl* decl = fn_decl_from_id(id, decl_unit);
                return get_or_create_user_fn(id, decl, decl_unit);
            }

            push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "call path depth > 2 not supported");
            return nullptr;
        }

        push_diag(Pass9Diagnostic::Code::InvalidCallee, loc, "unsupported callee expression kind");
        return nullptr;
    }

    // ---------------- Short-circuit ----------------

    llvm::Value* Pass9CodegenVisitor::emit_logical_and(ast::Expr* lhs, ast::Expr* rhs, const lex::Loc& loc)
    {
        // Both must be i1 (Pass 8 enforces for conditions; still guard)
        llvm::Function* fn = cur_llfn_;
        if (!fn) return llvm::ConstantInt::getFalse(ty_i1());

        llvm::BasicBlock* bb_lhs = bld_.GetInsertBlock();
        llvm::BasicBlock* bb_rhs = llvm::BasicBlock::Create(llctx_, "and.rhs", fn);
        llvm::BasicBlock* bb_end = llvm::BasicBlock::Create(llctx_, "and.end", fn);

        llvm::Value* v_lhs = emit_expr(lhs);
        if (!v_lhs || v_lhs->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, loc, "logical_and lhs is not bool");
            v_lhs = llvm::ConstantInt::getFalse(ty_i1());
        }

        bld_.CreateCondBr(v_lhs, bb_rhs, bb_end);

        // rhs
        bld_.SetInsertPoint(bb_rhs);
        llvm::Value* v_rhs = emit_expr(rhs);
        if (!v_rhs || v_rhs->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, loc, "logical_and rhs is not bool");
            v_rhs = llvm::ConstantInt::getFalse(ty_i1());
        }
        bld_.CreateBr(bb_end);

        // end
        bld_.SetInsertPoint(bb_end);
        auto* phi = bld_.CreatePHI(ty_i1(), 2, "and.phi");
        phi->addIncoming(llvm::ConstantInt::getFalse(ty_i1()), bb_lhs);
        phi->addIncoming(v_rhs, bb_rhs);
        return phi;
    }

    llvm::Value* Pass9CodegenVisitor::emit_logical_or(ast::Expr* lhs, ast::Expr* rhs, const lex::Loc& loc)
    {
        llvm::Function* fn = cur_llfn_;
        if (!fn) return llvm::ConstantInt::getFalse(ty_i1());

        llvm::BasicBlock* bb_lhs = bld_.GetInsertBlock();
        llvm::BasicBlock* bb_rhs = llvm::BasicBlock::Create(llctx_, "or.rhs", fn);
        llvm::BasicBlock* bb_end = llvm::BasicBlock::Create(llctx_, "or.end", fn);

        llvm::Value* v_lhs = emit_expr(lhs);
        if (!v_lhs || v_lhs->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, loc, "logical_or lhs is not bool");
            v_lhs = llvm::ConstantInt::getFalse(ty_i1());
        }

        bld_.CreateCondBr(v_lhs, bb_end, bb_rhs);

        // rhs
        bld_.SetInsertPoint(bb_rhs);
        llvm::Value* v_rhs = emit_expr(rhs);
        if (!v_rhs || v_rhs->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, loc, "logical_or rhs is not bool");
            v_rhs = llvm::ConstantInt::getFalse(ty_i1());
        }
        bld_.CreateBr(bb_end);

        // end
        bld_.SetInsertPoint(bb_end);
        auto* phi = bld_.CreatePHI(ty_i1(), 2, "or.phi");
        phi->addIncoming(llvm::ConstantInt::getTrue(ty_i1()), bb_lhs);
        phi->addIncoming(v_rhs, bb_rhs);
        return phi;
    }

    // ---------------- Expr emission ----------------

    llvm::Value* Pass9CodegenVisitor::emit_expr(ast::Expr* e)
    {
        if (!e)
            return nullptr;

        e->accept(*this);
        return last_v_;
    }

    // ---------------- Visitor: Module ----------------

    void Pass9CodegenVisitor::visit(ast::Module& m)
    {
        if (unit_index_ < p45_.envs.size())
            env_ = &p45_.envs[unit_index_];
        else
            env_ = nullptr;

        ast::visitor::OverallVisitor::visit(m);

        env_ = nullptr;
    }

    // ---------------- Visitor: FnDecl ----------------

    void Pass9CodegenVisitor::visit(ast::FnDecl& f)
    {
        // Find FnId for this function via Pass4 module table:
        // We assume Pass4 assigned FnId by module_id + index in mg.fns.
        // We locate index by scanning mg.fns for decl pointer == &f.
        if (unit_index_ >= p4_.modules.size())
            return;

        const ModuleGlobals& mg = p4_.modules[unit_index_];
        std::optional<FnId> id_opt;

        for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(mg.fns.size()); ++i)
        {
            if (mg.fns[i].decl == &f)
            {
                id_opt = mg.fns[i].id;
                break;
            }
        }

        if (!id_opt.has_value())
        {
            // If function wasn't indexed, skip
            return;
        }

        const FnId id = *id_opt;

        // Create (or get) LLVM function declaration
        llvm::Function* llfn = get_or_create_user_fn(id, &f, unit_index_);
        if (!llfn) return;

        // If no body, skip codegen (could be extern-like in future)
        if (!f.body_) return;

        // Fetch Pass6 bindings for this function
        if (unit_index_ >= p6_.modules.size())
            return;

        auto& mod_bind = p6_.modules[unit_index_];
        auto itb = mod_bind.fns.find(id);
        if (itb == mod_bind.fns.end())
        {
            push_diag(Pass9Diagnostic::Code::MissingBinding, f.location_, "missing Pass6 bindings for function");
            return;
        }

        cur_fn_bind_ = &itb->second;
        cur_llfn_ = llfn;

        // Create entry block
        cur_entry_ = llvm::BasicBlock::Create(llctx_, "entry", llfn);
        bld_.SetInsertPoint(cur_entry_);

        // Allocate slots
        slot_allocas_.clear();
        slot_allocas_.resize(cur_fn_bind_->slot_count, nullptr);

        for (std::uint32_t s = 0; s < cur_fn_bind_->slot_count; ++s)
        {
            auto* a = bld_.CreateAlloca(ty_objp(), nullptr, "slot" + std::to_string(s));
            slot_allocas_[s] = a;

            // Initialize to null (safety)
            bld_.CreateStore(llvm::ConstantPointerNull::get(ty_objp()), a);
        }

        // Store parameters into their slots if Pass6 created param slots
        // Convention: param_decl != nullptr indicates slot belongs to param
        // We iterate slots in order and assign args sequentially to param slots encountered.
        std::size_t arg_i = 0;
        for (auto& arg : llfn->args())
        {
            // Find the param slot info for this argument
            // Simplest: assume first N slots correspond to params in order of params_.
            // If your Pass6 uses a different policy, replace this mapping.
            if (arg_i < f.params_.size())
            {
                // find slot for param decl pointer
                ast::ParamDecl* pd = f.params_[arg_i];
                if (pd)
                {
                    for (const auto& info : cur_fn_bind_->slots)
                    {
                        if (info.param_decl == pd)
                        {
                            const std::uint32_t idx = info.slot.index;
                            if (idx < slot_allocas_.size())
                                bld_.CreateStore(&arg, slot_allocas_[idx]);
                            break;
                        }
                    }
                }
            }
            ++arg_i;
        }

        // Emit body
        f.body_->accept(*this);

        // Ensure function has a terminator
        if (!is_terminated())
        {
            if (fn_returns_void(f))
                bld_.CreateRetVoid();
            else
                bld_.CreateRet(llvm::ConstantPointerNull::get(ty_objp()));
        }

        // Clear fn context
        cur_fn_bind_ = nullptr;
        cur_llfn_ = nullptr;
        cur_entry_ = nullptr;
        slot_allocas_.clear();
        loop_stack_.clear();
    }

    void Pass9CodegenVisitor::visit(ast::ParamDecl& p)
    {
        (void)p;
        // No direct IR for param nodes; handled in FnDecl prologue.
    }

    // ---------------- Visitor: Block ----------------

    void Pass9CodegenVisitor::visit(ast::BlockStatement& b)
    {
        for (auto* s : b.statements_)
        {
            if (!s) continue;
            if (is_terminated()) break;
            s->accept(*this);
        }
    }

    // ---------------- Visitor: VarStmt ----------------

    void Pass9CodegenVisitor::visit(ast::VarStmt& v)
    {
        // VarStmt itself is already assigned a slot in Pass6 (via RefExpr uses),
        // but VarStmt node doesn't carry the SlotId.
        // So we support initialization by finding a slot that points to this var decl.
        if (!cur_fn_bind_) return;

        std::optional<std::uint32_t> slot_index;
        for (const auto& info : cur_fn_bind_->slots)
        {
            if (info.var_decl == &v)
            {
                slot_index = info.slot.index;
                break;
            }
        }

        if (!slot_index.has_value() || *slot_index >= slot_allocas_.size())
        {
            // If Pass6 didn't allocate a slot for this var, skip.
            return;
        }

        llvm::Value* initv = llvm::ConstantPointerNull::get(ty_objp());
        if (v.init_)
        {
            llvm::Value* rhs = emit_expr(v.init_);
            // Pass8: rhs should be Obj for var init (unless user writes bool into obj var)
            // In your language, types exist, but we’re dynamic here; store Obj* only.
            if (rhs && rhs->getType() == ty_objp())
                initv = rhs;
            else
                initv = llvm::ConstantPointerNull::get(ty_objp());
        }

        bld_.CreateStore(initv, slot_allocas_[*slot_index]);
    }

    // ---------------- Visitor: ExprStatement ----------------

    void Pass9CodegenVisitor::visit(ast::ExprStatement& e)
    {
        if (e.expr_) (void)emit_expr(e.expr_);
    }

    // ---------------- Visitor: Return ----------------

    void Pass9CodegenVisitor::visit(ast::ReturnStatement& r)
    {
        if (!cur_llfn_) return;

        const bool ret_void = cur_llfn_->getReturnType()->isVoidTy();

        if (ret_void)
        {
            // ignore return expr (or evaluate for side effects if you want)
            bld_.CreateRetVoid();
            return;
        }

        llvm::Value* rv = llvm::ConstantPointerNull::get(ty_objp());
        if (r.expr_)
        {
            llvm::Value* v = emit_expr(r.expr_);
            if (v && v->getType() == ty_objp())
                rv = v;
            else
            {
                push_diag(Pass9Diagnostic::Code::ReturnTypeMismatch, r.location_,
                          "return expression is not Obj* for non-void function");
            }
        }

        bld_.CreateRet(rv);
    }

    // ---------------- Visitor: If / While / DoWhile ----------------

    void Pass9CodegenVisitor::visit(ast::IfStatement& i)
    {
        if (!cur_llfn_) return;

        llvm::Value* cond = emit_expr(i.condition_);
        if (!cond || cond->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, i.location_, "if condition must be bool (i1)");
            cond = llvm::ConstantInt::getFalse(ty_i1());
        }

        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(llctx_, "if.then", cur_llfn_);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(llctx_, "if.else", cur_llfn_);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(llctx_, "if.end", cur_llfn_);

        bld_.CreateCondBr(cond, thenBB, elseBB);

        // then
        bld_.SetInsertPoint(thenBB);
        if (i.thenBody_) i.thenBody_->accept(*this);
        if (!is_terminated()) bld_.CreateBr(endBB);

        // else-if chain and else: simplest lowering
        // We lower else-if list as nested ifs in elseBB.
        bld_.SetInsertPoint(elseBB);

        // Build nested chain:
        llvm::BasicBlock* curElse = elseBB;
        for (auto* eif : i.elseIfs_)
        {
            if (!eif) continue;

            llvm::Value* c = emit_expr(eif->condition_);
            if (!c || c->getType() != ty_i1())
            {
                push_diag(Pass9Diagnostic::Code::UnsupportedExpr, eif->location_,
                          "else-if condition must be bool (i1)");
                c = llvm::ConstantInt::getFalse(ty_i1());
            }

            llvm::BasicBlock* eifThen = llvm::BasicBlock::Create(llctx_, "eif.then", cur_llfn_);
            llvm::BasicBlock* eifElse = llvm::BasicBlock::Create(llctx_, "eif.else", cur_llfn_);

            bld_.CreateCondBr(c, eifThen, eifElse);

            bld_.SetInsertPoint(eifThen);
            if (eif->then_) eif->then_->accept(*this);
            if (!is_terminated()) bld_.CreateBr(endBB);

            // continue in eifElse
            bld_.SetInsertPoint(eifElse);
            curElse = eifElse;
        }

        // final else
        if (i.else_ && i.else_->then_)
        {
            i.else_->then_->accept(*this);
        }
        if (!is_terminated()) bld_.CreateBr(endBB);

        // end
        bld_.SetInsertPoint(endBB);
    }

    void Pass9CodegenVisitor::visit(ast::WhileStatement& w)
    {
        if (!cur_llfn_) return;

        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(llctx_, "while.cond", cur_llfn_);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(llctx_, "while.body", cur_llfn_);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(llctx_, "while.end", cur_llfn_);

        bld_.CreateBr(condBB);

        // cond
        bld_.SetInsertPoint(condBB);
        llvm::Value* cond = emit_expr(w.condition_);
        if (!cond || cond->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, w.location_, "while condition must be bool (i1)");
            cond = llvm::ConstantInt::getFalse(ty_i1());
        }
        bld_.CreateCondBr(cond, bodyBB, endBB);

        // body
        bld_.SetInsertPoint(bodyBB);
        loop_stack_.push_back({.break_bb = endBB, .cont_bb = condBB});
        if (w.body_) w.body_->accept(*this);
        loop_stack_.pop_back();
        if (!is_terminated()) bld_.CreateBr(condBB);

        // end
        bld_.SetInsertPoint(endBB);
    }

    void Pass9CodegenVisitor::visit(ast::DoWhileStatement& d)
    {
        if (!cur_llfn_) return;

        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(llctx_, "do.body", cur_llfn_);
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(llctx_, "do.cond", cur_llfn_);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(llctx_, "do.end", cur_llfn_);

        bld_.CreateBr(bodyBB);

        // body
        bld_.SetInsertPoint(bodyBB);
        loop_stack_.push_back({.break_bb = endBB, .cont_bb = condBB});
        if (d.body_) d.body_->accept(*this);
        loop_stack_.pop_back();
        if (!is_terminated()) bld_.CreateBr(condBB);

        // cond
        bld_.SetInsertPoint(condBB);
        llvm::Value* cond = emit_expr(d.condition_);
        if (!cond || cond->getType() != ty_i1())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, d.location_, "do-while condition must be bool (i1)");
            cond = llvm::ConstantInt::getFalse(ty_i1());
        }
        bld_.CreateCondBr(cond, bodyBB, endBB);

        // end
        bld_.SetInsertPoint(endBB);
    }

    void Pass9CodegenVisitor::visit(ast::BreakStatement& b)
    {
        if (loop_stack_.empty())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedStmt, b.location_, "break outside of loop");
            return;
        }
        bld_.CreateBr(loop_stack_.back().break_bb);
    }

    void Pass9CodegenVisitor::visit(ast::ContinueStatement& c)
    {
        if (loop_stack_.empty())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedStmt, c.location_, "continue outside of loop");
            return;
        }
        bld_.CreateBr(loop_stack_.back().cont_bb);
    }

    // ---------------- Visitor: Literals ----------------

    void Pass9CodegenVisitor::visit(ast::BoolLiteralExpr& b)
    {
        last_v_ = llvm::ConstantInt::get(ty_i1(), b.v_ ? 1 : 0);
    }

    void Pass9CodegenVisitor::visit(ast::IntLiteralExpr& i)
    {
        auto it = p7_.int_id.find(&i);
        if (it == p7_.int_id.end() || it->second >= p7_.ints.size())
        {
            // fallback null
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }

        const auto& lit = p7_.ints[it->second];

        std::uint64_t u = 0;
        std::visit([&](auto v) { u = static_cast<std::uint64_t>(v); }, lit);

        last_v_ = emit_box_int_u64(u);
    }

    void Pass9CodegenVisitor::visit(ast::FloatLiteralExpr& f)
    {
        auto it = p7_.float_id.find(&f);
        if (it == p7_.float_id.end() || it->second >= p7_.floats.size())
        {
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }

        const auto& lit = p7_.floats[it->second];

        double d = 0.0;
        std::visit([&](auto v) { d = static_cast<double>(v); }, lit);

        last_v_ = emit_box_float_f64(d);
    }

    void Pass9CodegenVisitor::visit(ast::CharLiteralExpr& c)
    {
        // Not implemented: treat as null Obj* for now
        (void)c;
        last_v_ = llvm::ConstantPointerNull::get(ty_objp());
    }

    void Pass9CodegenVisitor::visit(ast::StringLiteralExpr& s)
    {
        // Not implemented: treat as null Obj* for now
        (void)s;
        last_v_ = llvm::ConstantPointerNull::get(ty_objp());
    }

    // ---------------- Visitor: RefExpr ----------------

    void Pass9CodegenVisitor::visit(ast::RefExpr& r)
    {
        auto b = get_binding(r);
        if (!b.has_value())
        {
            push_diag(Pass9Diagnostic::Code::MissingBinding, r.location_, "missing binding for ref");
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }

        if (b->kind == BindingKind::LocalSlot)
        {
            const std::uint32_t idx = b->slot.index;
            if (idx >= slot_allocas_.size())
            {
                push_diag(Pass9Diagnostic::Code::MissingBinding, r.location_, "slot index out of range");
                last_v_ = llvm::ConstantPointerNull::get(ty_objp());
                return;
            }

            last_v_ = bld_.CreateLoad(ty_objp(), slot_allocas_[idx], "ld");
            return;
        }

        // Functions are not first-class. If this is used as expression, return null.
        if (b->kind == BindingKind::GlobalFn)
        {
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }

        last_v_ = llvm::ConstantPointerNull::get(ty_objp());
    }

    // ---------------- Visitor: AssignExpr ----------------

    void Pass9CodegenVisitor::visit(ast::AssignExpr& a)
    {
        // Support: lhs is RefExpr bound to LocalSlot
        auto* lhs_ref = dynamic_cast<ast::RefExpr*>(a.lhs_);
        if (!lhs_ref)
        {
            push_diag(Pass9Diagnostic::Code::AssignToNonLocal, a.location_,
                      "assignment lhs must be a local ref (for now)");
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            if (a.rhs_) (void)emit_expr(a.rhs_);
            return;
        }

        auto b = get_binding(*lhs_ref);
        if (!b.has_value() || b->kind != BindingKind::LocalSlot)
        {
            push_diag(Pass9Diagnostic::Code::AssignToNonLocal, a.location_, "assignment lhs is not a local slot");
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            if (a.rhs_) (void)emit_expr(a.rhs_);
            return;
        }

        llvm::Value* rhs = emit_expr(a.rhs_);
        if (!rhs || rhs->getType() != ty_objp())
        {
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, a.location_, "assignment rhs must be Obj*");
            rhs = llvm::ConstantPointerNull::get(ty_objp());
        }

        const std::uint32_t idx = b->slot.index;
        if (idx < slot_allocas_.size())
            bld_.CreateStore(rhs, slot_allocas_[idx]);

        // Assignment yields the assigned value (Obj*)
        last_v_ = rhs;
    }

    // ---------------- Visitor: UnaryExpr ----------------

    void Pass9CodegenVisitor::visit(ast::UnaryExpr& u)
    {
        using U = ast::UnaryOp;

        if (u.op == U::logical_not)
        {
            llvm::Value* v = emit_expr(u.expr_);
            if (!v || v->getType() != ty_i1())
            {
                push_diag(Pass9Diagnostic::Code::UnsupportedExpr, u.location_, "! requires bool (i1)");
                v = llvm::ConstantInt::getFalse(ty_i1());
            }
            last_v_ = bld_.CreateNot(v, "not");
            return;
        }

        if (u.op == U::negation)
        {
            llvm::Value* v = emit_expr(u.expr_);
            if (!v || v->getType() != ty_objp())
            {
                push_diag(Pass9Diagnostic::Code::UnsupportedExpr, u.location_, "unary - requires Obj* number");
                last_v_ = llvm::ConstantPointerNull::get(ty_objp());
                return;
            }

            // Call rt_neg if provided
            auto* fty = llvm::FunctionType::get(ty_objp(), {ty_objp()}, false);
            auto* fn = get_or_declare_runtime(abi_.rt_neg, fty);
            last_v_ = bld_.CreateCall(fn, {v}, "neg");
            return;
        }

        // Others not supported yet (inc/dec/deref require lvalue rules)
        push_diag(Pass9Diagnostic::Code::UnsupportedExpr, u.location_, "unsupported unary op in Pass9");
        if (u.expr_) (void)emit_expr(u.expr_);
        last_v_ = llvm::ConstantPointerNull::get(ty_objp());
    }

    // ---------------- Visitor: BinaryExpr ----------------

    void Pass9CodegenVisitor::visit(ast::BinaryExpr& b)
    {
        using Op = ast::BinaryOp;

        if (b.op == Op::logical_and)
        {
            last_v_ = emit_logical_and(b.lhs_, b.rhs_, b.location_);
            return;
        }

        if (b.op == Op::logical_or)
        {
            last_v_ = emit_logical_or(b.lhs_, b.rhs_, b.location_);
            return;
        }

        // comparisons return i1
        auto emit_cmp = [&](std::string_view rtname) -> llvm::Value*
        {
            llvm::Value* l = emit_expr(b.lhs_);
            llvm::Value* r = emit_expr(b.rhs_);
            if (!l || !r || l->getType() != ty_objp() || r->getType() != ty_objp())
            {
                push_diag(Pass9Diagnostic::Code::UnsupportedExpr, b.location_, "comparison operands must be Obj*");
                return llvm::ConstantInt::getFalse(ty_i1());
            }
            auto* fty = llvm::FunctionType::get(ty_i1(), {ty_objp(), ty_objp()}, false);
            auto* fn = get_or_declare_runtime(rtname, fty);
            return bld_.CreateCall(fn, {l, r}, "cmp");
        };

        switch (b.op)
        {
        case Op::equal: last_v_ = emit_cmp(abi_.rt_eq);
            return;
        case Op::not_equal: last_v_ = emit_cmp(abi_.rt_ne);
            return;
        case Op::less: last_v_ = emit_cmp(abi_.rt_lt);
            return;
        case Op::less_equal: last_v_ = emit_cmp(abi_.rt_le);
            return;
        case Op::greater: last_v_ = emit_cmp(abi_.rt_gt);
            return;
        case Op::greater_equal: last_v_ = emit_cmp(abi_.rt_ge);
            return;
        default:
            break;
        }

        // arithmetic returns Obj*
        auto emit_bin = [&](std::string_view rtname) -> llvm::Value*
        {
            llvm::Value* l = emit_expr(b.lhs_);
            llvm::Value* r = emit_expr(b.rhs_);
            if (!l || !r || l->getType() != ty_objp() || r->getType() != ty_objp())
            {
                push_diag(Pass9Diagnostic::Code::UnsupportedExpr, b.location_, "arithmetic operands must be Obj*");
                return llvm::ConstantPointerNull::get(ty_objp());
            }
            auto* fty = llvm::FunctionType::get(ty_objp(), {ty_objp(), ty_objp()}, false);
            auto* fn = get_or_declare_runtime(rtname, fty);
            return bld_.CreateCall(fn, {l, r}, "bin");
        };

        switch (b.op)
        {
        case Op::add: last_v_ = emit_bin(abi_.rt_add);
            return;
        case Op::subtract: last_v_ = emit_bin(abi_.rt_sub);
            return;
        case Op::multiply: last_v_ = emit_bin(abi_.rt_mul);
            return;
        case Op::divide: last_v_ = emit_bin(abi_.rt_div);
            return;
        case Op::modulo: last_v_ = emit_bin(abi_.rt_mod);
            return;
        default:
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, b.location_, "unsupported binary op in Pass9");
            if (b.lhs_) (void)emit_expr(b.lhs_);
            if (b.rhs_) (void)emit_expr(b.rhs_);
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }
    }

    // ---------------- Visitor: CallExpr ----------------

    void Pass9CodegenVisitor::visit(ast::CallExpr& c)
    {
        llvm::Function* callee = resolve_callee(c.callee_, c.location_);
        if (!callee)
        {
            push_diag(Pass9Diagnostic::Code::InvalidCallee, c.location_, "cannot resolve callee");
            // still eval args for side effects
            for (auto* a : c.args_) if (a) (void)emit_expr(a);
            last_v_ = llvm::ConstantPointerNull::get(ty_objp());
            return;
        }

        // Emit args as Obj* (dynamic). If an arg expression is i1, that is currently unsupported.
        std::vector<llvm::Value*> args;
        args.reserve(c.args_.size());

        for (auto* a : c.args_)
        {
            llvm::Value* v = emit_expr(a);
            if (!v)
            {
                args.push_back(llvm::ConstantPointerNull::get(ty_objp()));
                continue;
            }

            if (v->getType() == ty_objp())
            {
                args.push_back(v);
                continue;
            }

            // bool passed as value is not supported in this minimal ABI
            push_diag(Pass9Diagnostic::Code::UnsupportedExpr, c.location_,
                      "passing bool (i1) as argument not supported yet");
            args.push_back(llvm::ConstantPointerNull::get(ty_objp()));
        }

        llvm::CallInst* call = bld_.CreateCall(callee, args);

        if (callee->getReturnType()->isVoidTy())
        {
            last_v_ = nullptr;
            return;
        }

        // returns Obj*
        last_v_ = call;
    }

    // ---------------- Visitor: PathExpr ----------------

    void Pass9CodegenVisitor::visit(ast::PathExpr& p)
    {
        // Path used as expression is not supported (functions not first-class).
        (void)p;
        last_v_ = llvm::ConstantPointerNull::get(ty_objp());
    }

    // ---------------- Driver ----------------

    Pass9Result run_pass9_codegen(const Translation& tr,
                                  const Pass2Result& p2,
                                  const Pass4Result& p4,
                                  const Pass4_5Result& p45,
                                  const Pass6Result& p6,
                                  const Pass7Result& p7,
                                  const Pass8Result& p8,
                                  llvm::LLVMContext& llctx,
                                  const RuntimeAbi& abi)
    {
        Pass9Result out{};
        out.module = std::make_unique<llvm::Module>("kl_module", llctx);

        // Phase 1: create LLVM function declarations for all functions (so calls work)
        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(p4.modules.size()); ++unit_i)
        {
            const ModuleGlobals& mg = p4.modules[unit_i];
            for (const FnSym& fs : mg.fns)
            {
                if (!fs.decl) continue;

                // Create prototype
                Pass9CodegenVisitor proto(p2, p4, p45, p6, p7, p8, abi, out, llctx, *out.module, unit_i);
                (void)proto.get_or_create_user_fn(fs.id, fs.decl, unit_i);
            }
        }

        // Phase 2: emit bodies
        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass9CodegenVisitor vis(p2, p4, p45, p6, p7, p8, abi, out, llctx, *out.module, unit_i);
            m->accept(vis);
        }

        // Optional: verify
        // llvm::verifyModule(*out.module, &llvm::errs());

        return out;
    }
} // namespace sema
