#pragma once

#include "logging_entities.hpp"

#include <memory>
#include <string>
#include <unordered_map>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/ADT/StringRef.h>

#include "translation.hpp"
#include "type_system.hpp"

namespace sema
{
    // Forward declarations (these are your existing compiler types)
    struct Pass4Result;
    struct ModuleGlobals;
    struct LoadFnSym;

    // -----------------------------
    // Pass 9.1 output state
    // -----------------------------
    struct Pass9_1RuntimeDecls
    {
        // core
        llvm::Function* rt_alloc{};
        llvm::Function* rt_free{};
        llvm::Function* rt_print{};
        llvm::Function* rt_put{};
        llvm::Function* rt_nl{};

        // boxing
        llvm::Function* rt_box_bool{};
        llvm::Function* rt_unbox_bool{};

        // numeric ctors
        llvm::Function* rt_int_from_u64{};
        llvm::Function* rt_int_from_i64{};
        llvm::Function* rt_int_from_u128{};
        llvm::Function* rt_int_from_i128{};
        llvm::Function* rt_float_from_f32{};
        llvm::Function* rt_float_from_f64{};

        // ops
        llvm::Function* rt_add{};
        llvm::Function* rt_sub{};
        llvm::Function* rt_mul{};
        llvm::Function* rt_div{};
        llvm::Function* rt_mod{};
        llvm::Function* rt_neg{};

        // comparisons
        llvm::Function* rt_eq{};
        llvm::Function* rt_ne{};
        llvm::Function* rt_lt{};
        llvm::Function* rt_le{};
        llvm::Function* rt_gt{};
        llvm::Function* rt_ge{};

        // Box intrinsics
        llvm::Function* box_new{};
        llvm::Function* box_free{};
        llvm::Function* box_len{};
        llvm::Function* box_get{};
        llvm::Function* box_set{};
        llvm::Function* rt_ref_store{};
        llvm::Function* rt_ref_load{}; // Obj* rt_ref_load(Obj* ref)
        llvm::Function* rt_ref_from_slot{};

        // Struct runtime
        llvm::Function* rt_struct_new{};
        llvm::Function* rt_struct_set_field{};
        llvm::Function* rt_struct_get_field{};

        llvm::Function* rt_struct_field_slot{}; // Obj** rt_struct_field_slot(Obj* structObj, i64 fieldIndex)
        llvm::Function* rt_box_elem_slot{};
        llvm::Function* rt_retain{};
        llvm::Function* rt_release{};
        llvm::Function* rt_char_from_u32{};
    };

    struct Pass9_1Result
    {
        std::unique_ptr<llvm::LLVMContext> llctx;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;

        // core types
        llvm::Type* void_ty{};
        llvm::IntegerType* i1_ty{};
        llvm::IntegerType* i8_ty{};
        llvm::IntegerType* i32_ty{};
        llvm::IntegerType* i64_ty{};
        llvm::IntegerType* u64_ty{};
        llvm::Type* obj_ptr_ty{}; // Obj* (opaque ptr or i8*)

        Pass9_1RuntimeDecls runtime{};

        // load-fn declarations (key type depends on your codebase; replace as needed)
        // Example: std::unordered_map<LoadFnId, llvm::Function*> load_fn_decls;
        std::unordered_map<LoadFnId, llvm::Function*, LocalIdHash<LoadFnTag>> load_fn_decls;
        std::unordered_map<FnId, llvm::Function*, LocalIdHash<FnTag>> fn_decls;

        const ast::Module* log_mod = nullptr;
        std::vector<const ast::Module*> unit_mods;
        LogSequence errors;
    };

    // -----------------------------
    // Shared IR helpers
    // -----------------------------
    // -----------------------------
    // Pass entry points
    // -----------------------------
    Pass9_1Result run_pass9_1_bootstrap(const Translation& tr,
                                        const std::string& module_name);
} // namespace sema
