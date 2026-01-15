#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "translation.hpp"

// inputs
#include "pass4.hpp"     // FnId
#include "pass6.hpp"     // FnBindings / slots / slot_count
#include "pass9_1_bootstrap.hpp"   // Pass9_1Result (LLVM module + builder + types)
#include "pass9_3_declare_load_fns.hpp"   // Pass9_3Result (declared user fn prototypes)

// LLVM
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>

namespace sema
{
    struct Pass9_4Diagnostic final
    {
        enum class Code : uint8_t
        {
            MissingUserFnPrototype,   // Pass9.3 didn't create llvm::Function* for a FnId
            FnAlreadyHasBody,         // unexpected (should not happen if 9.3 only declared)
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct FramePlan final
    {
        FnId fn_id{};
        ast::FnDecl* decl = nullptr;

        llvm::Function* llvm_fn = nullptr;
        llvm::BasicBlock* entry = nullptr;

        // index == SlotId.index
        std::vector<llvm::AllocaInst*> slot_allocas;

        // how many param slots we initialized with stores
        uint32_t param_slot_count = 0;
    };

    struct Pass9_4Result final
    {
        std::unordered_map<FnId, FramePlan, LocalIdHash<FnTag>> frames;
        std::vector<Pass9_4Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
    };

    Pass9_4Result run_pass9_4_plan_function_frames(const Translation& tr,
                                                   const Pass4Result& p4,
                                                   const Pass6Result& p6,
                                                   Pass9_1Result& p91,
                                                   const Pass9_3Result& p93);
} // namespace sema
