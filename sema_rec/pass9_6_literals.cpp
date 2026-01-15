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
    // ------------------------------------------------------------
    // Logging helpers (module-path-first cluster head)
    // ------------------------------------------------------------
    static const std::vector<lex::SymId>& pass9_mod_path(const Pass9_1Result& st)
    {
        static const std::vector<lex::SymId> kEmpty{};
        if (st.log_mod && st.log_mod->pathExpr_)
            return st.log_mod->pathExpr_->path_;
        return kEmpty;
    }

    static void log_begin(LogSequence& seq, const Pass9_1Result& st, const lex::Loc& loc)
    {
        seq.emplace_back(LogPath{SymKind::Ident, pass9_mod_path(st), loc});
    }

    static void log_err(LogSequence& seq, const Pass9_1Result& st, const lex::Loc& loc, std::string msg)
    {
        log_begin(seq, st, loc);
        log_msg(seq, std::move(msg));
    }

    // ------------------------------------------------------------
    // LLVM helpers
    // ------------------------------------------------------------
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

    static llvm::Function* get_or_declare_checked(Pass9_6Result& out,
                                                  Pass9_1Result& st,
                                                  llvm::FunctionType* FT,
                                                  llvm::StringRef name,
                                                  const lex::Loc& loc = {})
    {
        if (!st.module)
        {
            log_err(out.errors, st, loc, "pass9.6: internal: st.module is null");
            return nullptr;
        }

        llvm::Module& M = *st.module;

        if (auto* F = M.getFunction(name))
        {
            if (!same_fty(F->getFunctionType(), FT))
            {
                log_err(out.errors, st, loc,
                        ("pass9.6: RuntimeCtorTypeMismatch: runtime symbol already declared with different type: " +
                         name.str()));
                return nullptr;
            }
            return F;
        }

        return llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, M);
    }

    static llvm::Value* null_obj(Pass9_1Result& st)
    {
        if (auto* PT = llvm::dyn_cast<llvm::PointerType>(st.obj_ptr_ty))
            return llvm::ConstantPointerNull::get(PT);
        return llvm::Constant::getNullValue(st.obj_ptr_ty);
    }

    // ------------------------------------------------------------
    // Prepare (declare checked ctor symbols)
    // ------------------------------------------------------------
    Pass9_6Result run_pass9_6_prepare(Pass9_1Result& st)
    {
        Pass9_6Result out{};

        if (!st.llctx || !st.module)
        {
            log_err(out.errors, st, lex::Loc{},
                    "pass9.6: MissingLLVMState: missing LLVM context or module (pass9.1 not initialized?)");
            return out;
        }

        if (!st.obj_ptr_ty || !st.i64_ty)
        {
            log_err(out.errors, st, lex::Loc{},
                    "pass9.6: MissingLLVMState: missing canonical types (obj_ptr_ty / i64_ty)");
            return out;
        }

        llvm::LLVMContext& C = *st.llctx;

        auto* i128 = llvm::IntegerType::get(C, 128);
        auto* f32  = llvm::Type::getFloatTy(C);
        auto* f64  = llvm::Type::getDoubleTy(C);

        out.ctors.int_i64 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {st.i64_ty}, false), "rt_int_from_i64");

        out.ctors.int_u64 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {st.i64_ty}, false), "rt_int_from_u64");

        out.ctors.int_i128 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {i128}, false), "rt_int_from_i128");

        out.ctors.int_u128 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {i128}, false), "rt_int_from_u128");

        out.ctors.f32 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {f32}, false), "rt_float_from_f32");

        out.ctors.f64 = get_or_declare_checked(
            out, st, llvm::FunctionType::get(st.obj_ptr_ty, {f64}, false), "rt_float_from_f64");

        // If any ctor is null, treat as error (already logged).
        if (!out.ctors.int_i64 || !out.ctors.int_u64 || !out.ctors.int_i128 || !out.ctors.int_u128 ||
            !out.ctors.f32 || !out.ctors.f64)
        {
            // no extra log needed
        }

        return out;
    }

    // ------------------------------------------------------------
    // Literal emission (requires prepared ctors)
    // ------------------------------------------------------------

#if defined(__SIZEOF_INT128__)
    static llvm::APInt apint_u128(unsigned __int128 u)
    {
        const uint64_t lo = static_cast<uint64_t>(u);
        const uint64_t hi = static_cast<uint64_t>(u >> 64);
        uint64_t words[2]{lo, hi}; // least significant first
        return llvm::APInt(128, llvm::ArrayRef<uint64_t>(words, 2));
    }
#endif

    template <class T>
    struct IntInfo
    {
        static constexpr bool is_signed = std::is_signed_v<T>;
        static constexpr unsigned bits  = static_cast<unsigned>(sizeof(T) * 8u);
    };

    llvm::Value* emit_int_literal_obj(Pass9_1Result& st,
                                      llvm::IRBuilder<>& B,
                                      const Pass7Result& p7,
                                      const ast::IntLiteralExpr& lit,
                                      const Pass9_6RtCtors& rt)
    {
        auto it_id = p7.int_id.find(&lit);
        if (it_id == p7.int_id.end())
            return null_obj(st);

        const uint32_t id = it_id->second;
        if (id >= p7.ints.size())
            return null_obj(st);

        if (!st.llctx || !st.obj_ptr_ty || !st.i64_ty)
            return null_obj(st);

        const IntLitValue& v = p7.ints[id];

        return std::visit([&]<typename T0>(T0 vv) -> llvm::Value*
        {
            using T = T0;

#if defined(__SIZEOF_INT128__)
            constexpr bool is_i128 =
                std::is_same_v<T, __int128> || std::is_same_v<T, unsigned __int128>;
#else
            constexpr bool is_i128 = false;
#endif

            constexpr bool signed_k = std::is_signed_v<T>;
            constexpr unsigned bits = is_i128 ? 128u : IntInfo<T>::bits;

            if constexpr (!is_i128 && bits <= 64)
            {
                auto* TyN = llvm::IntegerType::get(*st.llctx, bits);

                llvm::Value* cN = nullptr;
                if constexpr (signed_k)
                    cN = llvm::ConstantInt::getSigned(TyN, static_cast<int64_t>(vv));
                else
                    cN = llvm::ConstantInt::get(TyN, static_cast<uint64_t>(vv), /*isSigned=*/false);

                llvm::Value* arg64 = signed_k
                    ? B.CreateSExtOrTrunc(cN, st.i64_ty, "sext.i64")
                    : B.CreateZExtOrTrunc(cN, st.i64_ty, "zext.u64");

                llvm::Function* ctor = signed_k ? rt.int_i64 : rt.int_u64;
                if (!ctor)
                    return null_obj(st);

                return B.CreateCall(ctor, {arg64}, "box.int");
            }
#if defined(__SIZEOF_INT128__)
            else if constexpr (is_i128)
            {
                auto* i128 = llvm::IntegerType::get(*st.llctx, 128);

                unsigned __int128 u = 0;
                if constexpr (std::is_same_v<T, __int128>)
                    u = static_cast<unsigned __int128>(vv); // preserve two's complement bits
                else
                    u = static_cast<unsigned __int128>(vv);

                llvm::APInt ap = apint_u128(u);
                llvm::Value* c128 = llvm::ConstantInt::get(i128, ap);

                llvm::Function* ctor = signed_k ? rt.int_i128 : rt.int_u128;
                if (!ctor)
                    return null_obj(st);

                return B.CreateCall(ctor, {c128}, "box.int128");
            }
#endif
            else
            {
                // Unsupported wider-than-64 without __int128 support
                return null_obj(st);
            }
        }, v);
    }

    llvm::Value* emit_float_literal_obj(Pass9_1Result& st,
                                        llvm::IRBuilder<>& B,
                                        const Pass7Result& p7,
                                        const ast::FloatLiteralExpr& lit,
                                        const Pass9_6RtCtors& rt)
    {
        auto it_id = p7.float_id.find(&lit);
        if (it_id == p7.float_id.end())
            return null_obj(st);

        const uint32_t id = it_id->second;
        if (id >= p7.floats.size())
            return null_obj(st);

        if (!st.llctx || !st.obj_ptr_ty)
            return null_obj(st);

        const FloatLitValue& v = p7.floats[id];

        return std::visit([&]<typename T0>(T0 vv) -> llvm::Value*
        {
            using T = T0;

            if constexpr (std::is_same_v<T, float>)
            {
                if (!rt.f32) return null_obj(st);
                llvm::Value* c = llvm::ConstantFP::get(llvm::Type::getFloatTy(*st.llctx), vv);
                return B.CreateCall(rt.f32, {c}, "box.f32");
            }
            else
            {
                if (!rt.f64) return null_obj(st);
                llvm::Value* c = llvm::ConstantFP::get(llvm::Type::getDoubleTy(*st.llctx),
                                                       static_cast<double>(vv));
                return B.CreateCall(rt.f64, {c}, "box.f64");
            }
        }, v);
    }
} // namespace sema
