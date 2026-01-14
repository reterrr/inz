#include "pass9_1_bootstrap.hpp"
#include "pass4.hpp"

#include <llvm/IR/Module.h>

#include "pass9_2_declare_user_fns.hpp"

namespace sema
{
    static llvm::Type* make_obj_ptr(llvm::LLVMContext& C)
    {
        return llvm::PointerType::get(C, 0); // opaque 'ptr'
    }

    // Declare load functions as external:
    // conservative ABI: (Obj*, Obj*, ...) -> Obj*


Pass9_1Result run_pass9_1_bootstrap(const Translation& tr,
                                const std::string& module_name)
    {
        Pass9_1Result st{};
        st.llctx = std::make_unique<llvm::LLVMContext>();
        st.module = std::make_unique<llvm::Module>(module_name, *st.llctx);
        st.builder = std::make_unique<llvm::IRBuilder<>>(*st.llctx);

        // NEW: pick any module for logging (pass9.2 is global wiring, not per-unit)
        st.log_mod = nullptr;
        st.unit_mods.clear();
        st.unit_mods.reserve(tr.units.size());

        for (const auto& u : tr.units)
        {
            st.unit_mods.push_back(u.module_);
            if (!st.log_mod && u.module_)
                st.log_mod = u.module_;
        }

        // Core types
        st.void_ty = llvm::Type::getVoidTy(*st.llctx);
        st.i1_ty   = llvm::Type::getInt1Ty(*st.llctx);
        st.i8_ty   = llvm::Type::getInt8Ty(*st.llctx);
        st.i32_ty  = llvm::Type::getInt32Ty(*st.llctx);
        st.i64_ty  = llvm::Type::getInt64Ty(*st.llctx);

        st.obj_ptr_ty = make_obj_ptr(*st.llctx);

        // 1) runtime declarations (fills st.runtime, logs on failure)
        run_pass9_2_declare_runtime(st);

        // 2) load-fn declarations
        return st;
    }
} // namespace sema
