#include "pass9_2_declare_user_fns.hpp"
#include "pass9_1_bootstrap.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

namespace sema
{
    static bool same_fty(const llvm::FunctionType* a, const llvm::FunctionType* b)
    {
        if (a == b) return true;
        if (!a || !b) return false;

        if (a->getReturnType() != b->getReturnType()) return false;
        if (a->isVarArg() != b->isVarArg()) return false;
        if (a->getNumParams() != b->getNumParams()) return false;

        for (unsigned i = 0; i < a->getNumParams(); ++i)
            if (a->getParamType(i) != b->getParamType(i))
                return false;

        return true;
    }

    [[noreturn]] static void runtime_wiring_fail(const char* symbol, const std::string& msg)
    {
        std::cerr << "[pass9.2 runtime wiring] fatal: " << msg << " (symbol: " << symbol << ")\n";
        std::abort();
    }

    static llvm::Function* get_or_declare_checked(Pass9_1Result& st,
                                                  llvm::FunctionType* expect,
                                                  const char* name)
    {
        assert(st.module && st.llctx);
        llvm::Module& M = *st.module;

        if (llvm::Function* F = M.getFunction(name))
        {
            llvm::FunctionType* have = F->getFunctionType();
            if (!same_fty(have, expect))
            {
                std::ostringstream oss;
                oss << "runtime symbol '" << name << "' already declared with a different LLVM function type";
                runtime_wiring_fail(name, oss.str());
            }
            return F;
        }

        return llvm::Function::Create(expect, llvm::Function::ExternalLinkage, name, M);
    }

    // ---------------------------------------------------------------------
    // Runtime wiring (Pass9.2 stage), NO Pass10
    // ---------------------------------------------------------------------
    static void run_pass9_2_runtime_wiring(Pass9_1Result& st)
    {
        if (!st.llctx || !st.module)
            runtime_wiring_fail("<module>", "Pass9.1 state missing LLVMContext/module");

        // Canonical types
        llvm::Type* Obj = st.obj_ptr_ty;          // Obj*
        llvm::Type* V   = st.void_ty;             // void
        llvm::IntegerType* I1  = st.i1_ty;        // i1
        llvm::IntegerType* I64 = st.i64_ty;       // i64

        if (!Obj || !V || !I1 || !I64)
            runtime_wiring_fail("<types>", "Pass9.1 missing canonical LLVM types");

        // Convenience LLVM types
        llvm::Type* I128 = llvm::Type::getInt128Ty(*st.llctx);
        llvm::Type* F32  = llvm::Type::getFloatTy(*st.llctx);
        llvm::Type* F64  = llvm::Type::getDoubleTy(*st.llctx);

        // ------------------------------------------------------------
        // Core allocator / printer
        // ------------------------------------------------------------
        st.runtime.rt_alloc = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I64}, false), "rt_alloc");

        st.runtime.rt_free = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj}, false), "rt_free");

        st.runtime.rt_print = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj}, false), "rt_print");

        // ------------------------------------------------------------
        // ARC (retain/release)
        // ------------------------------------------------------------
        st.runtime.rt_retain = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj}, false), "rt_retain");

        st.runtime.rt_release = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj}, false), "rt_release");

        // ------------------------------------------------------------
        // Bool boxing
        // ------------------------------------------------------------
        st.runtime.rt_box_bool = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I1}, false), "rt_box_bool");

        st.runtime.rt_unbox_bool = get_or_declare_checked(st,
            llvm::FunctionType::get(I1, {Obj}, false), "rt_unbox_bool");

        // ------------------------------------------------------------
        // Numeric ctors
        // ------------------------------------------------------------
        st.runtime.rt_int_from_u64 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I64}, false), "rt_int_from_u64");

        st.runtime.rt_int_from_i64 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I64}, false), "rt_int_from_i64");

        st.runtime.rt_int_from_u128 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I128}, false), "rt_int_from_u128");

        st.runtime.rt_int_from_i128 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I128}, false), "rt_int_from_i128");

        st.runtime.rt_float_from_f32 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {F32}, false), "rt_float_from_f32");

        st.runtime.rt_float_from_f64 = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {F64}, false), "rt_float_from_f64");

        // ------------------------------------------------------------
        // Numeric ops (Obj*, Obj*) -> Obj*
        // ------------------------------------------------------------
        llvm::FunctionType* obj2_obj = llvm::FunctionType::get(Obj, {Obj, Obj}, false);

        st.runtime.rt_add = get_or_declare_checked(st, obj2_obj, "rt_add");
        st.runtime.rt_sub = get_or_declare_checked(st, obj2_obj, "rt_sub");
        st.runtime.rt_mul = get_or_declare_checked(st, obj2_obj, "rt_mul");
        st.runtime.rt_div = get_or_declare_checked(st, obj2_obj, "rt_div");
        st.runtime.rt_mod = get_or_declare_checked(st, obj2_obj, "rt_mod");

        st.runtime.rt_neg = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj}, false), "rt_neg");

        // ------------------------------------------------------------
        // Comparisons (Obj*, Obj*) -> i1
        // ------------------------------------------------------------
        llvm::FunctionType* obj2_i1 = llvm::FunctionType::get(I1, {Obj, Obj}, false);

        st.runtime.rt_eq = get_or_declare_checked(st, obj2_i1, "rt_eq");
        st.runtime.rt_ne = get_or_declare_checked(st, obj2_i1, "rt_ne");
        st.runtime.rt_lt = get_or_declare_checked(st, obj2_i1, "rt_lt");
        st.runtime.rt_le = get_or_declare_checked(st, obj2_i1, "rt_le");
        st.runtime.rt_gt = get_or_declare_checked(st, obj2_i1, "rt_gt");
        st.runtime.rt_ge = get_or_declare_checked(st, obj2_i1, "rt_ge");

        // ------------------------------------------------------------
        // Ref ops
        // ------------------------------------------------------------
        st.runtime.rt_ref_store = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj, Obj}, false), "rt_ref_store");

        st.runtime.rt_ref_load = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj}, false), "rt_ref_load");

        // Obj* rt_ref_from_slot(Obj** slot_addr)
        {
            llvm::Type* ObjPtrPtr = st.obj_ptr_ty->getPointerTo(); // Obj**
            st.runtime.rt_ref_from_slot = get_or_declare_checked(st,
                llvm::FunctionType::get(Obj, {ObjPtrPtr}, false), "rt_ref_from_slot");
        }

        // ------------------------------------------------------------
        // Struct runtime
        // ------------------------------------------------------------
        st.runtime.rt_struct_new = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {I64, I64}, false), "rt_struct_new");

        st.runtime.rt_struct_set_field = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj, I64, Obj}, false), "rt_struct_set_field");

        st.runtime.rt_struct_get_field = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj, I64}, false), "rt_struct_get_field");

        // Slots: Obj** return
        llvm::Type* ObjPtr     = st.obj_ptr_ty;                       // Obj*
        llvm::Type* ObjSlotPtr = llvm::PointerType::getUnqual(ObjPtr); // Obj**

        auto* FT_struct_slot = llvm::FunctionType::get(
            ObjSlotPtr, {ObjPtr, st.i64_ty}, false);

        auto* FT_box_elem_slot = llvm::FunctionType::get(
            ObjSlotPtr, {ObjPtr, ObjPtr}, false); // index is boxed Obj*

        st.runtime.rt_struct_field_slot =
            llvm::cast<llvm::Function>(
                st.module->getOrInsertFunction("rt_struct_field_slot", FT_struct_slot).getCallee());

        st.runtime.rt_box_elem_slot =
            llvm::cast<llvm::Function>(
                st.module->getOrInsertFunction("rt_box_elem_slot", FT_box_elem_slot).getCallee());

        // ------------------------------------------------------------
        // Box API (TYPE-ERASED ABI)
        // ------------------------------------------------------------
        st.runtime.box_new = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj, I64, I64, I64}, false), "box_new");

        st.runtime.box_free = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj}, false), "box_free");

        st.runtime.box_len = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj}, false), "box_len");

        st.runtime.box_get = get_or_declare_checked(st,
            llvm::FunctionType::get(Obj, {Obj, Obj}, false), "box_get");

        st.runtime.box_set = get_or_declare_checked(st,
            llvm::FunctionType::get(V, {Obj, Obj, Obj}, false), "box_set");

        // ------------------------------------------------------------
        // Final sanity (fail fast)
        // ------------------------------------------------------------
        auto require = [&](llvm::Function* F, const char* nm)
        {
            if (!F)
            {
                std::ostringstream oss;
                oss << "internal error: runtime symbol pointer is null after wiring";
                runtime_wiring_fail(nm, oss.str());
            }
        };

        require(st.runtime.rt_alloc, "rt_alloc");
        require(st.runtime.rt_free, "rt_free");
        require(st.runtime.rt_print, "rt_print");

        require(st.runtime.rt_retain, "rt_retain");
        require(st.runtime.rt_release, "rt_release");

        require(st.runtime.rt_box_bool, "rt_box_bool");
        require(st.runtime.rt_unbox_bool, "rt_unbox_bool");

        require(st.runtime.rt_int_from_i64, "rt_int_from_i64");
        require(st.runtime.rt_int_from_u64, "rt_int_from_u64");
        require(st.runtime.rt_int_from_u128, "rt_int_from_u128");
        require(st.runtime.rt_int_from_i128, "rt_int_from_i128");
        require(st.runtime.rt_float_from_f32, "rt_float_from_f32");
        require(st.runtime.rt_float_from_f64, "rt_float_from_f64");

        require(st.runtime.rt_add, "rt_add");
        require(st.runtime.rt_sub, "rt_sub");
        require(st.runtime.rt_mul, "rt_mul");
        require(st.runtime.rt_div, "rt_div");
        require(st.runtime.rt_mod, "rt_mod");
        require(st.runtime.rt_neg, "rt_neg");

        require(st.runtime.rt_eq, "rt_eq");
        require(st.runtime.rt_ne, "rt_ne");
        require(st.runtime.rt_lt, "rt_lt");
        require(st.runtime.rt_le, "rt_le");
        require(st.runtime.rt_gt, "rt_gt");
        require(st.runtime.rt_ge, "rt_ge");

        require(st.runtime.rt_ref_store, "rt_ref_store");
        require(st.runtime.rt_ref_load, "rt_ref_load");
        require(st.runtime.rt_ref_from_slot, "rt_ref_from_slot");

        require(st.runtime.rt_struct_new, "rt_struct_new");
        require(st.runtime.rt_struct_set_field, "rt_struct_set_field");
        require(st.runtime.rt_struct_get_field, "rt_struct_get_field");
        require(st.runtime.rt_struct_field_slot, "rt_struct_field_slot");
        require(st.runtime.rt_box_elem_slot, "rt_box_elem_slot");

        require(st.runtime.box_new, "box_new");
        require(st.runtime.box_free, "box_free");
        require(st.runtime.box_len, "box_len");
        require(st.runtime.box_get, "box_get");
        require(st.runtime.box_set, "box_set");
    }

    // Public API used by the rest of your pipeline.
    Pass9_1RuntimeDecls& run_pass9_2_declare_runtime(Pass9_1Result& st)
    {
        run_pass9_2_runtime_wiring(st);
        return st.runtime;
    }
} // namespace sema
