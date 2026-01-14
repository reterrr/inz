// sema/pass9_2_declare_runtime.cpp
#include "pass9_2_declare_user_fns.hpp"
#include "pass9_1_bootstrap.hpp"

#include "logging_entities.hpp" // LogSequence, LogPath, Log, SymKind
#include "module/module.hpp"    // ast::Module (for pathExpr_->path_)

#include <cassert>
#include <cstdlib>
#include <sstream>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

namespace sema
{
    static bool same_fty(const llvm::FunctionType* a, const llvm::FunctionType* b)
    {
        if (a == b)
            return true;
        if (!a || !b)
            return false;

        if (a->getReturnType() != b->getReturnType())
            return false;
        if (a->isVarArg() != b->isVarArg())
            return false;
        if (a->getNumParams() != b->getNumParams())
            return false;

        for (unsigned i = 0; i < a->getNumParams(); ++i)
            if (a->getParamType(i) != b->getParamType(i))
                return false;

        return true;
    }

    // ------------------------------------------------------------
    // Logging helpers (REQUIRED: module path first in each cluster)
    // ------------------------------------------------------------

    static const std::vector<lex::SymId>&
    pass9_module_path(const Pass9_1Result& st)
    {
        static const std::vector<lex::SymId> kEmpty{};
        // ADAPT: pick the field you actually have.
        // Recommended: st.src_mod_for_logs set during pass9.1 bootstrap.
        if (st.log_mod && st.log_mod->pathExpr_)
            return st.log_mod->pathExpr_->path_;
        return kEmpty;
    }

    static void pass9_log_begin(Pass9_1Result& st, const lex::Loc& loc)
    {
        // REQUIRED: each error cluster begins with module path LogPath{Ident,
        // mod_path, loc}
        st.errors.emplace_back(LogPath{SymKind::Ident, pass9_module_path(st), loc});
    }

    [[noreturn]] static void runtime_wiring_fail(Pass9_1Result& st,
                                                 const char* symbol,
                                                 const std::string& msg,
                                                 const lex::Loc& loc = {})
    {
        pass9_log_begin(st, loc);

        std::ostringstream oss;
        oss << "pass9.2: RuntimeWiringFailure: " << msg;
        if (symbol && symbol[0] != '\0')
            oss << " (symbol: " << symbol << ")";

        st.errors.emplace_back(oss.str());

        // No SymId for runtime C symbols; keep the identifier in message.
        // Add an anchor entity so tooling has a location node even for internal
        // errors.
        st.errors.emplace_back(LogPath{SymKind::Ident, {}, loc});

        std::abort();
    }

    static llvm::Function* get_or_declare_checked(Pass9_1Result& st,
                                                  llvm::FunctionType* expect,
                                                  const char* name)
    {
        if (!st.module || !st.llctx)
            runtime_wiring_fail(st, "<module>",
                                "Pass9.1 state missing LLVMContext/module");

        llvm::Module& M = *st.module;

        if (llvm::Function* F = M.getFunction(name))
        {
            llvm::FunctionType* have = F->getFunctionType();
            if (!same_fty(have, expect))
            {
                std::ostringstream oss;
                oss << "runtime symbol '" << name
                    << "' already declared with a different LLVM function type";
                runtime_wiring_fail(st, name, oss.str());
            }
            return F;
        }

        return llvm::Function::Create(expect, llvm::Function::ExternalLinkage, name,
                                      M);
    }

    // ---------------------------------------------------------------------
    // Runtime wiring (Pass9.2 stage)
    // ---------------------------------------------------------------------
    static void run_pass9_2_runtime_wiring(Pass9_1Result& st)
    {
        if (!st.llctx || !st.module)
            runtime_wiring_fail(st, "<module>",
                                "Pass9.1 state missing LLVMContext/module");

        // Canonical types (opaque pointers supported)
        llvm::Type* Obj = st.obj_ptr_ty; // ptr (your runtime Obj*)
        llvm::Type* V = st.void_ty; // void
        llvm::IntegerType* I1 = st.i1_ty; // i1
        llvm::IntegerType* I32 = st.i32_ty; // i32
        llvm::IntegerType* I64 = st.i64_ty; // i64

        if (!Obj || !V || !I1 || !I32 || !I64)
            runtime_wiring_fail(st, "<types>", "Pass9.1 missing canonical LLVM types");

        // Convenience LLVM types
        llvm::Type* I128 = llvm::Type::getInt128Ty(*st.llctx);
        llvm::Type* F32 = llvm::Type::getFloatTy(*st.llctx);
        llvm::Type* F64 = llvm::Type::getDoubleTy(*st.llctx);

        // ------------------------------------------------------------
        // Core allocator / printer
        // ------------------------------------------------------------
        st.runtime.rt_alloc = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I64}, false), "rt_alloc");

        st.runtime.rt_free = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "rt_free");

        st.runtime.rt_print = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "rt_print");

        st.runtime.rt_put = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "rt_put");

        st.runtime.rt_nl = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {}, false), "rt_nl");

        // ------------------------------------------------------------
        // ARC (retain/release)
        // ------------------------------------------------------------
        st.runtime.rt_retain = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "rt_retain");

        st.runtime.rt_release = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "rt_release");

        // ------------------------------------------------------------
        // Bool boxing
        // ------------------------------------------------------------
        st.runtime.rt_box_bool = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I1}, false), "rt_box_bool");

        st.runtime.rt_unbox_bool = get_or_declare_checked(
            st, llvm::FunctionType::get(I1, {Obj}, false), "rt_unbox_bool");

        // ------------------------------------------------------------
        // Numeric constructors
        // ------------------------------------------------------------
        st.runtime.rt_int_from_u64 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I64}, false), "rt_int_from_u64");

        st.runtime.rt_int_from_i64 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I64}, false), "rt_int_from_i64");

        st.runtime.rt_int_from_u128 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I128}, false), "rt_int_from_u128");

        st.runtime.rt_int_from_i128 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I128}, false), "rt_int_from_i128");

        st.runtime.rt_float_from_f32 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {F32}, false), "rt_float_from_f32");

        st.runtime.rt_float_from_f64 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {F64}, false), "rt_float_from_f64");

        // ------------------------------------------------------------
        // Numeric ops (Obj*, Obj*) -> Obj*
        // ------------------------------------------------------------
        llvm::FunctionType* obj2_obj =
            llvm::FunctionType::get(Obj, {Obj, Obj}, false);

        st.runtime.rt_add = get_or_declare_checked(st, obj2_obj, "rt_add");
        st.runtime.rt_sub = get_or_declare_checked(st, obj2_obj, "rt_sub");
        st.runtime.rt_mul = get_or_declare_checked(st, obj2_obj, "rt_mul");
        st.runtime.rt_div = get_or_declare_checked(st, obj2_obj, "rt_div");
        st.runtime.rt_mod = get_or_declare_checked(st, obj2_obj, "rt_mod");

        st.runtime.rt_neg = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj}, false), "rt_neg");

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
        st.runtime.rt_ref_store = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj, Obj}, false), "rt_ref_store");

        st.runtime.rt_ref_load = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj}, false), "rt_ref_load");

        // NOTE: if you want to be explicit, define a Ptr =
        // llvm::PointerType::get(*st.llctx, 0) and use {Ptr} here. Using Obj is
        // acceptable under opaque pointers if Obj is "ptr".
        st.runtime.rt_ref_from_slot = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj}, false), "rt_ref_from_slot");

        // ------------------------------------------------------------
        // Struct runtime
        // ------------------------------------------------------------
        st.runtime.rt_struct_new = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I64, I64}, false), "rt_struct_new");

        st.runtime.rt_struct_set_field = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj, I64, Obj}, false),
            "rt_struct_set_field");

        st.runtime.rt_struct_get_field = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj, I64}, false),
            "rt_struct_get_field");

        st.runtime.rt_struct_field_slot = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj, I64}, false),
            "rt_struct_field_slot");

        st.runtime.rt_box_elem_slot = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj, Obj}, false), "rt_box_elem_slot");

        // ------------------------------------------------------------
        // Box API
        // ------------------------------------------------------------
        st.runtime.box_new = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj, I64, I64, I64}, false), "box_new");

        st.runtime.box_free = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj}, false), "box_free");

        st.runtime.box_len = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj}, false), "box_len");

        st.runtime.box_get = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {Obj, Obj}, false), "box_get");

        st.runtime.box_set = get_or_declare_checked(
            st, llvm::FunctionType::get(V, {Obj, Obj, Obj}, false), "box_set");

        // ------------------------------------------------------------
        // Char ctor
        // ------------------------------------------------------------
        st.runtime.rt_char_from_u32 = get_or_declare_checked(
            st, llvm::FunctionType::get(Obj, {I32}, false), "rt_char_from_u32");
    }

    Pass9_1RuntimeDecls& run_pass9_2_declare_runtime(Pass9_1Result& st)
    {
        run_pass9_2_runtime_wiring(st);
        return st.runtime;
    }
} // namespace sema
