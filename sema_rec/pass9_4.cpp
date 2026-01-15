#include "pass9_4.hpp"

#include <sstream>

#include <llvm/IR/IRBuilder.h>

#include "pass9_1_bootstrap.hpp"
#include "pass9_3_declare_load_fns.hpp"

namespace sema
{
    static void push_diag(std::vector<Pass9_4Diagnostic>& ds,
                          Pass9_4Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        ds.push_back(Pass9_4Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    static uint32_t count_param_slots(const FnBindings& fb)
    {
        uint32_t n = 0;
        for (const auto& s : fb.slots)
        {
            if (s.param_decl) ++n;
        }
        return n;
    }

    static llvm::AllocaInst* create_slot_alloca(Pass9_1Result& st,
                                                llvm::IRBuilder<>& B,
                                                llvm::Type* obj_ptr_ty,
                                                uint32_t slot_index)
    {
        // Name is helpful for debugging IR.
        std::string name = "slot." + std::to_string(slot_index);
        return B.CreateAlloca(obj_ptr_ty, nullptr, name);
    }

    Pass9_4Result run_pass9_4_plan_function_frames(const Translation& tr,
                                                   const Pass4Result& /*p4*/,
                                                   const Pass6Result& p6,
                                                   Pass9_1Result& p91,
                                                   const Pass9_3Result& p93)
    {
        Pass9_4Result out{};

        // ADAPT: whatever you named the “Obj*” type in Pass9.1.
        // Common patterns:
        //   - p91.obj_ptr_ty (llvm::Type*)
        //   - p91.types.obj_ptr
        // Here I assume:
        //   p91.obj_ptr_ty is a *pointer* type (i8* or %Obj*)
        llvm::Type* obj_ptr_ty = p91.obj_ptr_ty;
        if (!obj_ptr_ty)
        {
            // If you don't store it, you must define it in pass9.1 and expose it.
            // Do not continue silently: everything else depends on it.
            push_diag(out.diagnostics,
                      Pass9_4Diagnostic::Code::MissingUserFnPrototype,
                      lex::Loc{},
                      "internal error: Pass9.1 obj_ptr_ty is null");
            return out;
        }

        // Walk pass6 bindings per unit.
        const uint32_t n_units = static_cast<uint32_t>(tr.units.size());
        for (uint32_t unit_i = 0; unit_i < n_units; ++unit_i)
        {
            if (unit_i >= p6.modules.size())
                continue;

            const ModuleBindings& mb = p6.modules[unit_i];

            for (const auto& [fn_id, fb] : mb.fns)
            {
                if (!fb.decl || !fb.decl->body_)
                    continue;

                // Canonical lookup: Pass9.3 put prototypes into p91.fn_decls
                auto itF = p91.fn_decls.find(fn_id);
                llvm::Function* F = (itF != p91.fn_decls.end()) ? itF->second : nullptr;

                if (!F)
                {
                    std::ostringstream oss;
                    oss << "missing llvm prototype for user fn id (module="
                        << fn_id.module.value << ", index=" << fn_id.index << ")";
                    push_diag(out.diagnostics,
                              Pass9_4Diagnostic::Code::MissingUserFnPrototype,
                              fb.decl->location_,
                              oss.str());
                    continue;
                }

                if (!F->empty())
                {
                    push_diag(out.diagnostics,
                              Pass9_4Diagnostic::Code::FnAlreadyHasBody,
                              fb.decl->location_,
                              "llvm function already has basic blocks (pass9.4 ran twice or pass9.5 already emitted)");
                    continue;
                }

                llvm::BasicBlock* entry = llvm::BasicBlock::Create(*p91.llctx, "entry", F);
                p91.builder->SetInsertPoint(entry);

                FramePlan plan{};
                plan.fn_id = fn_id;
                plan.decl = fb.decl;
                plan.llvm_fn = F;
                plan.entry = entry;

                plan.slot_allocas.resize(fb.slot_count, nullptr);
                for (uint32_t i = 0; i < fb.slot_count; ++i)
                    plan.slot_allocas[i] = create_slot_alloca(p91, *p91.builder, p91.obj_ptr_ty, i);

                const uint32_t param_slots = count_param_slots(fb);
                plan.param_slot_count = param_slots;

                // You need runtime boxing if a param is i1 and slots are Obj*
                // Declare rt_box_bool once (or reuse your pass9.2 runtime decls).
                llvm::Function* rt_box_bool = nullptr;
                {
                    llvm::Module& M = *p91.module;
                    auto* FT = llvm::FunctionType::get(p91.obj_ptr_ty, {p91.i1_ty}, false);
                    if (auto* existing = M.getFunction("rt_box_bool")) rt_box_bool = existing;
                    else rt_box_bool = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "rt_box_bool", M);
                }

                uint32_t arg_i = 0;
                for (llvm::Argument& arg : F->args())
                {
                    if (arg_i >= param_slots)
                        break;

                    llvm::AllocaInst* slotA = plan.slot_allocas[arg_i];
                    if (!slotA)
                    {
                        ++arg_i;
                        continue;
                    }

                    llvm::Value* stored = nullptr;

                    if (arg.getType() == p91.obj_ptr_ty)
                    {
                        stored = &arg;
                    }
                    else if (arg.getType() == p91.i1_ty)
                    {
                        stored = p91.builder->CreateCall(rt_box_bool, {&arg}, "box.param.bool");
                    }
                    else
                    {
                        // If this happens, your ABI lowering produced an unexpected param type.
                        stored = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(p91.obj_ptr_ty));
                    }

                    p91.builder->CreateStore(stored, slotA);
                    ++arg_i;
                }

                out.frames.emplace(fn_id, std::move(plan));
            }
        }

        return out;
    }
} // namespace sema
