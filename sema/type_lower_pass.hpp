#ifndef INZ_SEMA_PASS5_CONST_LOWER_HPP
#define INZ_SEMA_PASS5_CONST_LOWER_HPP

#include <cstdint>
#include <vector>
#include <optional>
#include <variant>
#include <string>
#include <string_view>
#include <cstring>
#include <cerrno>
#include <cmath>
#include <limits>
#include <type_traits>

#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Hashing.h>

#include "compiler_context.hpp"
#include "hir/arena_holder.hpp"
#include "hir/arena.hpp"

#include "sema/module_import_pass.hpp"   // ModulePassDB, ModuleId, FileId, kInvalidModule
#include "sema/scope_pass.hpp"           // ScopePass2DB, FnRec etc.
#include "sema/decl_bind_pass.hpp"        // Pass3DB, SemaTypeId, TypeInterner

#include "types.hpp"

// -----------------------------------------------------------------------------
// ASSUMPTIONS / ADAPTATION NOTES
// - You have HIR expr nodes: hir::ExprLitInt and hir::ExprLitFloat exactly as you posted.
// - Negative numeric literals are represented as unary '-' applied to a positive literal (common design).
// - Pass5 does NOT rerun Pass3; it consumes Pass3DB (types interner).
// - You provide a SymId->string view callback: symView(sym) -> llvm::StringRef
//   (you said: "lex::SymId assume that in needed function i provide arg which can give string on lex::SymId by .view(sym)").
// - Traversal hooks are written with minimal assumptions; you will need to wire the recursion for your HIR expression shapes.
// -----------------------------------------------------------------------------

namespace sema
{
    using namespace kl::rt;
    // You used these names in your prompt. If you already have canonical typedefs, reuse them.

    // -----------------------------
    // Lowered literal representations (you requested these)
    // -----------------------------
    struct LitInt
    {
        using Value = std::variant<i8, u8, i16, u16, i32, u32, i64, u64, i128, u128>;
        Value value;
    };

    struct FloatLit
    {
        using FloatValue = std::variant<f32, f64>;
        FloatValue value;
    };

    // -----------------------------
    // Pass5 errors
    // -----------------------------
    enum class Pass5ErrKind : std::uint8_t
    {
        IntInvalidDigits,
        IntOverflow,
        IntKindMismatch,

        FloatInvalid,
        FloatOverflow,
        FloatKindMismatch,

        InternalUnexpectedExprShape
    };

    struct Pass5Error
    {
        Pass5ErrKind kind{};
        FileId file{};
        ModuleId module{kInvalidModule};
        lex::Loc loc{};
        lex::SymId sym{}; // original token symbol (best-effort)
        std::optional<kl::rt::IntKind> int_kind;
        std::optional<kl::rt::FloatKind> float_kind;
    };

    // -----------------------------
    // Storage: side-table keyed by (ModuleId, ExprId)
    // -----------------------------
    struct ExprKey
    {
        ModuleId mod{kInvalidModule};
        hir::ExprId expr{(hir::ExprId)~0u};

        friend bool operator==(const ExprKey& a, const ExprKey& b)
        {
            return a.mod == b.mod && a.expr == b.expr;
        }
    };

    struct ExprKeyInfo
    {
        static ExprKey getEmptyKey()
        {
            return {kInvalidModule, (hir::ExprId)~0u};
        }

        static ExprKey getTombstoneKey()
        {
            return {kInvalidModule, (hir::ExprId)~0u - 1};
        }

        static llvm::hash_code getHashValue(const ExprKey& k)
        {
            return llvm::hash_combine((std::uint32_t)k.mod, (std::uint32_t)k.expr);
        }

        static bool isEqual(const ExprKey& a, const ExprKey& b)
        {
            if (a.expr == ~0u || a.expr == (~0u - 1) || b.expr == ~0u || b.expr == (~0u - 1))
                return a.expr == b.expr;
            return a == b;
        }
    };

    struct ConstValue
    {
        SemaTypeId type{kInvalidSemaType}; // builtin type id (i8/u8/.../f32/f64) from Pass3 TypeInterner
        std::variant<LitInt, FloatLit> value;
        lex::Loc loc{};
    };

    struct Pass5DB
    {
        llvm::DenseMap<ExprKey, ConstValue, ExprKeyInfo> const_values;

        // Optional, but often useful: store inferred expr type for *all* expressions.
        // If you do not want this yet, remove it.
        // std::vector<std::vector<SemaTypeId>> expr_types;

        std::vector<Pass5Error> errors;
    };

    // Callback to view SymId text
    using SymViewFn = llvm::StringRef(*)(lex::SymId);

    // -----------------------------
    // Helpers: string normalization
    // - remove '_' separators
    // - keep prefixes 0x/0o/0b if present
    // -----------------------------
    static inline std::string normalizeNumberText(llvm::StringRef s)
    {
        std::string out;
        out.reserve(s.size());
        for (char c : s)
        {
            if (c == '_') continue;
            out.push_back(c);
        }
        return out;
    }

    static inline int digitValue(char c)
    {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return -1;
    }

    struct ParseIntResult
    {
        bool ok{false};
        u128 value{static_cast<u128>(0)};
        unsigned base{10};
    };

    static inline ParseIntResult parseU128Base(std::string_view s)
    {
        // supports:
        //  - decimal: 123
        //  - hex: 0xFF
        //  - bin: 0b1010
        //  - oct: 0o77
        ParseIntResult r{};

        if (s.empty())
            return r;

        unsigned base = 10;
        std::size_t i = 0;

        if (s.size() >= 2 && s[0] == '0')
        {
            const char p = s[1];
            if (p == 'x' || p == 'X')
            {
                base = 16;
                i = 2;
            }
            else if (p == 'b' || p == 'B')
            {
                base = 2;
                i = 2;
            }
            else if (p == 'o' || p == 'O')
            {
                base = 8;
                i = 2;
            }
        }

        if (i >= s.size())
            return r;

        u128 acc = 0;
        for (; i < s.size(); ++i)
        {
            const int dv = digitValue(s[i]);
            if (dv < 0 || (unsigned)dv >= base)
                return r;

            // acc = acc * base + dv with overflow check for u128
            const u128 ub = (u128)base;
            if (acc > (std::numeric_limits<u128>::max() - (u128)dv) / ub)
                return r; // overflow
            acc = acc * ub + (u128)dv;
        }

        r.ok = true;
        r.value = acc;
        r.base = base;
        return r;
    }

    // Convert u128 magnitude into requested IntKind (signed/unsigned) with range checks.
    static inline bool fitIntKind(u128 mag, kl::rt::IntKind k, LitInt& outLit)
    {
        switch (k)
        {
        case kl::rt::IntKind::I8:
            if (mag <= (u128)std::numeric_limits<i8>::max())
            {
                outLit.value = (i8)mag;
                return true;
            }
            return false;
        case kl::rt::IntKind::U8:
            if (mag <= (u128)std::numeric_limits<u8>::max())
            {
                outLit.value = (u8)mag;
                return true;
            }
            return false;

        case kl::rt::IntKind::I16:
            if (mag <= (u128)std::numeric_limits<i16>::max())
            {
                outLit.value = (i16)mag;
                return true;
            }
            return false;
        case kl::rt::IntKind::U16:
            if (mag <= (u128)std::numeric_limits<u16>::max())
            {
                outLit.value = (u16)mag;
                return true;
            }
            return false;

        case kl::rt::IntKind::I32:
            if (mag <= (u128)std::numeric_limits<i32>::max())
            {
                outLit.value = (i32)mag;
                return true;
            }
            return false;
        case kl::rt::IntKind::U32:
            if (mag <= (u128)std::numeric_limits<u32>::max())
            {
                outLit.value = (u32)mag;
                return true;
            }
            return false;

        case kl::rt::IntKind::I64:
            if (mag <= (u128)std::numeric_limits<i64>::max())
            {
                outLit.value = (i64)mag;
                return true;
            }
            return false;
        case kl::rt::IntKind::U64:
            if (mag <= (u128)std::numeric_limits<u64>::max())
            {
                outLit.value = (u64)mag;
                return true;
            }
            return false;

        case kl::rt::IntKind::I128:
            // __int128 max is 2^127-1
            if (mag <= (((u128)1 << 127) - 1))
            {
                outLit.value = (i128)mag;
                return true;
            }
            return false;
        case kl::rt::IntKind::U128:
            outLit.value = (u128)mag;
            return true;
        }
        return false;
    }

    static inline std::optional<kl::rt::IntKind> chooseSmallestIntKind(u128 mag, LitInt& outLit)
    {
        // Policy: prefer signed when possible, then unsigned of same width.
        // Order: i8,u8,i16,u16,i32,u32,i64,u64,i128,u128
        static constexpr kl::rt::IntKind order[] = {
            kl::rt::IntKind::I8, kl::rt::IntKind::U8,
            kl::rt::IntKind::I16, kl::rt::IntKind::U16,
            kl::rt::IntKind::I32, kl::rt::IntKind::U32,
            kl::rt::IntKind::I64, kl::rt::IntKind::U64,
            kl::rt::IntKind::I128, kl::rt::IntKind::U128
        };

        for (auto k : order)
        {
            LitInt tmp{};
            if (fitIntKind(mag, k, tmp))
            {
                outLit = std::move(tmp);
                return k;
            }
        }
        return std::nullopt;
    }

    static inline kl::rt::BuiltinTypeExprKind builtinForIntKind(kl::rt::IntKind k)
    {
        // ADAPT if your BuiltinTypeExprKind enumerators are named differently.
        // The code assumes you have builtin kinds mirroring IntKind.
        switch (k)
        {
        case kl::rt::IntKind::I8: return kl::rt::BuiltinTypeExprKind::I8;
        case kl::rt::IntKind::U8: return kl::rt::BuiltinTypeExprKind::U8;
        case kl::rt::IntKind::I16: return kl::rt::BuiltinTypeExprKind::I16;
        case kl::rt::IntKind::U16: return kl::rt::BuiltinTypeExprKind::U16;
        case kl::rt::IntKind::I32: return kl::rt::BuiltinTypeExprKind::I32;
        case kl::rt::IntKind::U32: return kl::rt::BuiltinTypeExprKind::U32;
        case kl::rt::IntKind::I64: return kl::rt::BuiltinTypeExprKind::I64;
        case kl::rt::IntKind::U64: return kl::rt::BuiltinTypeExprKind::U64;
        case kl::rt::IntKind::I128: return kl::rt::BuiltinTypeExprKind::I128;
        case kl::rt::IntKind::U128: return kl::rt::BuiltinTypeExprKind::U128;
        }
        return kl::rt::BuiltinTypeExprKind::I32;
    }

    static inline kl::rt::BuiltinTypeExprKind builtinForFloatKind(kl::rt::FloatKind k)
    {
        switch (k)
        {
        case kl::rt::FloatKind::F32: return kl::rt::BuiltinTypeExprKind::F32;
        case kl::rt::FloatKind::F64: return kl::rt::BuiltinTypeExprKind::F64;
        }
        return kl::rt::BuiltinTypeExprKind::F64;
    }

    struct LowerIntOut
    {
        LitInt lit;
        kl::rt::IntKind chosen_kind;
    };

    struct LowerFloatOut
    {
        FloatLit lit;
        kl::rt::FloatKind chosen_kind;
    };

    // -----------------------------
    // Literal lowering (core algorithms)
    // -----------------------------
    static inline std::optional<LowerIntOut> lowerIntLiteral(
        llvm::StringRef raw,
        std::optional<kl::rt::IntKind> forcedKind,
        LitInt& tmpLit,
        kl::rt::IntKind& chosenKind,
        Pass5ErrKind& errKind)
    {
        const std::string norm = normalizeNumberText(raw);
        const auto parsed = parseU128Base(norm);
        if (!parsed.ok)
        {
            // ambiguous: invalid digits or overflow; we treat as invalid if overflow is the reason too.
            // If you want a better diag, separate overflow vs digit validation in parse.
            errKind = Pass5ErrKind::IntInvalidDigits;
            return std::nullopt;
        }

        const u128 mag = parsed.value;

        if (forcedKind.has_value())
        {
            LitInt out{};
            if (!fitIntKind(mag, *forcedKind, out))
            {
                errKind = Pass5ErrKind::IntKindMismatch;
                return std::nullopt;
            }
            tmpLit = std::move(out);
            chosenKind = *forcedKind;
            return LowerIntOut{tmpLit, chosenKind};
        }

        LitInt out{};
        auto k = chooseSmallestIntKind(mag, out);
        if (!k.has_value())
        {
            errKind = Pass5ErrKind::IntOverflow;
            return std::nullopt;
        }

        tmpLit = std::move(out);
        chosenKind = *k;
        return LowerIntOut{tmpLit, chosenKind};
    }

    static inline std::optional<LowerFloatOut> lowerFloatLiteral(
        llvm::StringRef raw,
        std::optional<kl::rt::FloatKind> forcedKind,
        FloatLit& tmpLit,
        kl::rt::FloatKind& chosenKind,
        Pass5ErrKind& errKind)
    {
        const std::string norm = normalizeNumberText(raw);

        // Parse using strtold. (from_chars(float) is not consistently available across stdlibs)
        errno = 0;
        char* endp = nullptr;
        const long double v = std::strtold(norm.c_str(), &endp);

        if (endp == norm.c_str() || *endp != '\0' || errno == ERANGE)
        {
            errKind = Pass5ErrKind::FloatInvalid;
            return std::nullopt;
        }

        auto canFitF32 = [&]() -> bool
        {
            const f32 f = (f32)v;
            if (!std::isfinite((double)v) && std::isfinite((double)f)) return false; // odd case
            if (std::isfinite((double)v) && !std::isfinite((double)f)) return false; // overflow to inf
            return true;
        };

        auto canFitF64 = [&]() -> bool
        {
            const f64 d = (f64)v;
            if (std::isfinite((double)v) && !std::isfinite(d)) return false;
            return true;
        };

        if (forcedKind.has_value())
        {
            if (*forcedKind == kl::rt::FloatKind::F32)
            {
                if (!canFitF32())
                {
                    errKind = Pass5ErrKind::FloatKindMismatch;
                    return std::nullopt;
                }
                tmpLit.value = (f32)v;
                chosenKind = kl::rt::FloatKind::F32;
                return LowerFloatOut{tmpLit, chosenKind};
            }
            else
            {
                if (!canFitF64())
                {
                    errKind = Pass5ErrKind::FloatKindMismatch;
                    return std::nullopt;
                }
                tmpLit.value = (f64)v;
                chosenKind = kl::rt::FloatKind::F64;
                return LowerFloatOut{tmpLit, chosenKind};
            }
        }

        // No kind: choose smallest possible float type.
        if (canFitF32())
        {
            tmpLit.value = (f32)v;
            chosenKind = kl::rt::FloatKind::F32;
            return LowerFloatOut{tmpLit, chosenKind};
        }
        if (canFitF64())
        {
            tmpLit.value = (f64)v;
            chosenKind = kl::rt::FloatKind::F64;
            return LowerFloatOut{tmpLit, chosenKind};
        }

        errKind = Pass5ErrKind::FloatOverflow;
        return std::nullopt;
    }

    // -----------------------------
    // Pass5 runner
    // -----------------------------
    struct Pass5Config
    {
        // If you want: treat integer literals without kind as signed-only unless overflow then unsigned, etc.
        // Currently fixed inside chooseSmallestIntKind().
        bool dummy{false};
    };

    struct Pass5
    {
        const ModulePassDB& p1;
        const ScopePass2DB& p2;
        const Pass3DB& p3; // consume Pass3 types interner
        hir::ArenaHolder& holder;
        CompilerContext& ctx;

        Pass5DB& out;

        Pass5(const ModulePassDB& p1_,
              const ScopePass2DB& p2_,
              const Pass3DB& p3_,
              hir::ArenaHolder& h_,
              CompilerContext& sv_,
              Pass5DB& o_)
            : p1(p1_), p2(p2_), p3(p3_), holder(h_), ctx(sv_), out(o_)
        {
        }

        void pushErr(Pass5ErrKind k, FileId file, ModuleId mod, const lex::Loc& loc,
                     lex::SymId sym,
                     std::optional<kl::rt::IntKind> ik = std::nullopt,
                     std::optional<kl::rt::FloatKind> fk = std::nullopt)
        {
            out.errors.push_back(Pass5Error{
                .kind = k,
                .file = file,
                .module = mod,
                .loc = loc,
                .sym = sym,
                .int_kind = ik,
                .float_kind = fk
            });
        }

        void visitStmt(ModuleId mod, FileId file, hir::Arena& ar, hir::StmtId sid)
        {
            auto& st = ar.stmts[(size_t)sid];

            std::visit([&]<typename S>(S& node)
            {
                using T = std::decay_t<S>;

                if constexpr (std::is_same_v<T, hir::StmtExpr>)
                {
                    visitExpr(mod, file, ar, node.expr);
                }
                else
                {
                    // Add other stmt kinds here when you have them:
                    // - let/var stmt: visit initializer expr
                    // - return stmt: visit returned expr
                    // - if/while/for: visit condition + nested blocks
                    // - etc.
                }
            }, st.kind);
        }

        // ---- Core entry: walk all expressions and lower int/float literals ----

        // You MUST adapt recursion to your HIR expression graph.
        // This function contains only the lowering behavior + a few common recursion shapes.
        void visitExpr(ModuleId mod, FileId file, hir::Arena& ar, hir::ExprId eid)
        {
            auto& ex = ar.exprs[(size_t)eid];

            std::visit([&]<typename E>(E& node)
            {
                using T = std::decay_t<E>;

                // -----------------------
                // INT literal
                // -----------------------
                if constexpr (std::is_same_v<T, hir::ExprLitInt>)
                {
                    const llvm::StringRef text = ctx.numericInterner.view(node.sym);

                    LitInt lit{};
                    kl::rt::IntKind chosen{};
                    Pass5ErrKind ek{};

                    auto lowered = lowerIntLiteral(text, node.kind, lit, chosen, ek);
                    if (!lowered.has_value())
                    {
                        pushErr(ek, file, mod, node.loc, node.sym, node.kind, std::nullopt);
                        return;
                    }

                    const SemaTypeId ty = const_cast<TypeInterner&>(p3.types)
                        .internBuiltin(builtinForIntKind(chosen));

                    out.const_values.try_emplace(
                        ExprKey{mod, eid},
                        ConstValue{
                            .type = ty,
                            .value = LitInt{lit.value},
                            .loc = node.loc
                        }
                    );

                    return;
                }

                // -----------------------
                // FLOAT literal
                // -----------------------
                else if constexpr (std::is_same_v<T, hir::ExprLitFloat>)
                {
                    const llvm::StringRef text = ctx.numericInterner.view(node.sym);

                    FloatLit lit{};
                    kl::rt::FloatKind chosen{};
                    Pass5ErrKind ek{};

                    auto lowered = lowerFloatLiteral(text, node.kind, lit, chosen, ek);
                    if (!lowered.has_value())
                    {
                        pushErr(ek, file, mod, node.loc, node.sym, std::nullopt, node.kind);
                        return;
                    }

                    const SemaTypeId ty = const_cast<TypeInterner&>(p3.types)
                        .internBuiltin(builtinForFloatKind(chosen));

                    out.const_values.try_emplace(
                        ExprKey{mod, eid},
                        ConstValue{
                            .type = ty,
                            .value = FloatLit{lit.value},
                            .loc = node.loc
                        }
                    );
                    return;
                }

                // -----------------------
                // Recursion for other expr nodes:
                // Adapt these patterns to your concrete HIR.
                // -----------------------

                // Example 1: unary expression with `inner`
                else if constexpr (requires { node.inner; })
                {
                    visitExpr(mod, file, ar, node.inner);
                    return;
                }

                // Example 2: binary expression with `lhs` and `rhs`
                else if constexpr (requires { node.lhs; node.rhs; })
                {
                    visitExpr(mod, file, ar, node.lhs);
                    visitExpr(mod, file, ar, node.rhs);
                    return;
                }

                // Example 3: call expression with `callee` and `args` (vector<ExprId>)
                else if constexpr (requires { node.callee; node.args; })
                {
                    visitExpr(mod, file, ar, node.callee);
                    for (auto a : node.args)
                        visitExpr(mod, file, ar, a);
                    return;
                }

                // Example 4: block expression with `stmts` / `tail` (you must adapt)
                else if constexpr (requires { node.stmts; })
                {
                    for (auto sid : node.stmts)
                    {
                        // If you have stmt->expr, adapt here.
                        // out.errors.push_back(...); // or traverse stmt children.
                        (void)sid;
                    }
                    if constexpr (requires { node.tail; })
                    {
                        if (node.tail.has_value())
                            visitExpr(mod, file, ar, *node.tail);
                    }
                    return;
                }

                // Fallback: do nothing. (You can choose to emit an internal error.)
                else
                {
                    // If you want strict coverage:
                    // pushErr(Pass5ErrKind::InternalUnexpectedExprShape, file, mod, ex.loc, lex::SymId{});
                    return;
                }
            }, ex.kind);
        }

        // Visit a function body. You must adapt to your HIR block representation.
        void visitFnBody(ModuleId mod, FileId file, hir::Arena& ar, hir::BlockId bid)
        {
            auto& b = ar.blocks[(size_t)bid];

            for (auto sid : b.stmts)
                visitStmt(mod, file, ar, sid);
        }

        void run()
        {
            out.const_values.clear();
            out.errors.clear();

            // Walk functions recorded in pass2 (stable, avoids scanning decls blindly).
            for (std::uint32_t fid = 0; fid < (std::uint32_t)p2.fns.size(); ++fid)
            {
                const auto& fr = p2.fns[(size_t)fid];

                if (fr.is_load)
                    continue;

                const ModuleId mod = fr.owner;
                const FileId file = (mod == kPreludeOwner) ? FileId{} : p1.modules[(size_t)mod].file;
                hir::Arena& ar = holder.arenas_[(size_t)mod];

                // Read decl
                auto& decl = ar.decls[(size_t)fr.decl_id];

                std::visit([&]<typename D>(D& node)
                {
                    using T = std::decay_t<D>;
                    if constexpr (std::is_same_v<T, hir::FnDecl>)
                    {
                        // Body stored in pass2 FnRec as fr.body too; either is fine.
                        visitFnBody(mod, file, ar, node.body);
                    }
                    else
                    {
                        // not expected (LoadFnDecl filtered), ignore
                    }
                }, decl.kind);
            }

            // If you also have global initializers, consts, etc., traverse those here.
        }
    };

    // Public entry point: consumes pass1/pass2/pass3 and produces pass5
    inline Pass5DB runPass5ConstLowering(const ModulePassDB& p1,
                                         const ScopePass2DB& p2,
                                         const Pass3DB& p3,
                                         hir::ArenaHolder& holder,
                                         CompilerContext& ctx)
    {
        Pass5DB out;
        Pass5 pass{p1, p2, p3, holder, ctx, out};
        pass.run();
        return out;
    }
} // namespace sema

#endif // INZ_SEMA_PASS5_CONST_LOWER_HPP
