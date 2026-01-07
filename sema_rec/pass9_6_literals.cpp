#include "pass9_6_literals.hpp"

#include <type_traits>

#include <llvm/ADT/APInt.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

namespace sema
{
    static llvm::Function* get_or_declare(llvm::Module& M,
                                          llvm::FunctionType* FT,
                                          llvm::StringRef name)
    {
        if (auto* F = M.getFunction(name))
            return F;
        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        // Works for both typed pointers and opaque pointers (still a PointerType instance).
        if (auto* PT = llvm::dyn_cast<llvm::PointerType>(st.obj_ptr_ty))
            return llvm::ConstantPointerNull::get(PT);

        // Fallback: for safety (should not happen if obj_ptr_ty is pointer-like)
        return llvm::Constant::getNullValue(st.obj_ptr_ty);
    }

    static void push_diag(Pass9_6Result& out,
                          Pass9_6Diagnostic::Code c,
                          std::string msg)
    {
        out.diagnostics.push_back(Pass9_6Diagnostic{
            .code = c,
            .loc = lex::Loc{},
            .message = std::move(msg),
        });
    }

    Pass9_6Result run_pass9_6_prepare(Pass9_1Result& st)
    {
        Pass9_6Result out{};

        if (!st.llctx || !st.module)
        {
            push_diag(out,
                      Pass9_6Diagnostic::Code::MissingLLVMState,
                      "pass9.6: missing LLVM context or module (pass9.1 not initialized?)");
            return out;
        }

        if (!st.obj_ptr_ty || !st.i64_ty)
        {
            push_diag(out,
                      Pass9_6Diagnostic::Code::MissingLLVMState,
                      "pass9.6: missing required canonical types (obj_ptr_ty / i64_ty)");
            return out;
        }

        llvm::LLVMContext& C = *st.llctx;
        llvm::Module& M = *st.module;

        auto* i128 = llvm::IntegerType::get(C, 128);
        auto* f32  = llvm::Type::getFloatTy(C);
        auto* f64  = llvm::Type::getDoubleTy(C);

        // Int constructors
        out.ctors.int_i64 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {st.i64_ty}, false),
            "rt_int_from_i64"
        );

        out.ctors.int_u64 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {st.i64_ty}, false),
            "rt_int_from_u64"
        );

        out.ctors.int_i128 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {i128}, false),
            "rt_int_from_i128"
        );

        out.ctors.int_u128 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {i128}, false),
            "rt_int_from_u128"
        );

        // Float constructors
        out.ctors.f32 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {f32}, false),
            "rt_float_from_f32"
        );

        out.ctors.f64 = get_or_declare(
            M,
            llvm::FunctionType::get(st.obj_ptr_ty, {f64}, false),
            "rt_float_from_f64"
        );

        return out;
    }

    // Make a 128-bit APInt from an unsigned __int128 bitpattern.
    static llvm::APInt apint_u128(unsigned __int128 u)
    {
        const uint64_t lo = static_cast<uint64_t>(u);
        const uint64_t hi = static_cast<uint64_t>(u >> 64);
        uint64_t words[2]{lo, hi}; // little-endian words (least significant first)
        return llvm::APInt(128, llvm::ArrayRef<uint64_t>(words, 2));
    }

    template <class T>
    struct IntInfo
    {
        static constexpr bool is_signed = std::is_signed_v<T>;
        static constexpr unsigned bits =
            (std::is_same_v<T, __int128_t> || std::is_same_v<T, unsigned __int128>)
                ? 128u
                : static_cast<unsigned>(sizeof(T) * 8u);
    };

    llvm::Value* emit_int_literal_obj(Pass9_1Result& st,
                                      llvm::IRBuilder<>& B,
                                      const Pass7Result& p7,
                                      const ast::IntLiteralExpr& lit)
    {
        auto it_id = p7.int_id.find(&lit);
        if (it_id == p7.int_id.end())
            return null_obj(st);

        const uint32_t id = it_id->second;
        if (id >= p7.ints.size())
            return null_obj(st);

        const IntLitValue& v = p7.ints[id];

        Pass9_6Result prep = run_pass9_6_prepare(st);
        if (!prep.ok())
            return null_obj(st);

        const Pass9_6RtCtors& rt = prep.ctors;

        return std::visit([&]<typename T0>(T0 vv) -> llvm::Value*
        {
            using T = T0;
            constexpr bool signed_k = IntInfo<T>::is_signed;
            constexpr unsigned bits = IntInfo<T>::bits;

            llvm::Value* cN = nullptr;

            if constexpr (bits <= 64)
            {
                auto* TyN = llvm::IntegerType::get(*st.llctx, bits);

                if constexpr (signed_k)
                {
                    // Interpret vv as signed with proper sign.
                    const int64_t s = static_cast<int64_t>(vv);
                    cN = llvm::ConstantInt::getSigned(TyN, s);
                }
                else
                {
                    const uint64_t u = static_cast<uint64_t>(vv);
                    cN = llvm::ConstantInt::get(TyN, u, /*isSigned=*/false);
                }

                llvm::Value* arg64 = signed_k
                    ? B.CreateSExt(cN, st.i64_ty, "sext.i64")
                    : B.CreateZExt(cN, st.i64_ty, "zext.u64");

                llvm::Function* ctor = signed_k ? rt.int_i64 : rt.int_u64;
                return B.CreateCall(ctor, {arg64}, "box.int");
            }
            else
            {
                // 128-bit value: use bitpattern
                unsigned __int128 u = 0;

                if constexpr (std::is_same_v<T, __int128_t>)
                {
                    __int128_t s = vv;
                    u = static_cast<unsigned __int128>(s);
                }
                else
                {
                    u = static_cast<unsigned __int128>(vv);
                }

                llvm::APInt ap = apint_u128(u);
                auto* i128 = llvm::IntegerType::get(*st.llctx, 128);
                llvm::Value* c128 = llvm::ConstantInt::get(i128, ap);

                llvm::Function* ctor = signed_k ? rt.int_i128 : rt.int_u128;
                return B.CreateCall(ctor, {c128}, "box.int128");
            }
        }, v);
    }

    llvm::Value* emit_float_literal_obj(Pass9_1Result& st,
                                        llvm::IRBuilder<>& B,
                                        const Pass7Result& p7,
                                        const ast::FloatLiteralExpr& lit)
    {
        auto it_id = p7.float_id.find(&lit);
        if (it_id == p7.float_id.end())
            return null_obj(st);

        const uint32_t id = it_id->second;
        if (id >= p7.floats.size())
            return null_obj(st);

        const FloatLitValue& v = p7.floats[id];

        Pass9_6Result prep = run_pass9_6_prepare(st);
        if (!prep.ok())
            return null_obj(st);

        const Pass9_6RtCtors& rt = prep.ctors;

        return std::visit([&]<typename T0>(T0 vv) -> llvm::Value*
        {
            using T = T0;

            if constexpr (std::is_same_v<T, float>)
            {
                llvm::Value* c = llvm::ConstantFP::get(llvm::Type::getFloatTy(*st.llctx), vv);
                return B.CreateCall(rt.f32, {c}, "box.f32");
            }
            else
            {
                // treat everything else as double
                llvm::Value* c = llvm::ConstantFP::get(llvm::Type::getDoubleTy(*st.llctx), static_cast<double>(vv));
                return B.CreateCall(rt.f64, {c}, "box.f64");
            }
        }, v);
    }

} // namespace sema
