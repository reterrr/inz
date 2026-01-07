// sema/pass7.cpp

#include "pass7.hpp"
#include "compiler_context.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

// Expr/stmt nodes used by Pass7 typing
#include "stmt/var_statement.hpp"
#include "expr/assign_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/path_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/array_literal_expr.hpp"

namespace sema
{
    // ============================================================
    // Diagnostics helper
    // ============================================================

    static void push_diag(Pass7Result& out,
                          Pass7Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        out.diagnostics.push_back(Pass7Diagnostic{
            .code = c,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    // ============================================================
    // Pass7 (A): literal lowering
    // ============================================================

    class Pass7LiteralLoweringVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass7LiteralLoweringVisitor(const CompilerContext& ctx, Pass7Result& out)
            : ctx_(ctx), out_(out)
        {
        }

        void visit(ast::IntLiteralExpr&) override;
        void visit(ast::FloatLiteralExpr&) override;
        void visit(ast::ArrayLiteralExpr& a) override;

    private:
        const CompilerContext& ctx_;
        Pass7Result& out_;

        static std::string strip_underscores(std::string_view s)
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

        static int detect_base(std::string_view s, std::string_view& digits)
        {
            if (s.size() >= 2 && s[0] == '0')
            {
                if (s[1] == 'x' || s[1] == 'X')
                {
                    digits = s.substr(2);
                    return 16;
                }
                if (s[1] == 'b' || s[1] == 'B')
                {
                    digits = s.substr(2);
                    return 2;
                }
                if (s[1] == 'o' || s[1] == 'O')
                {
                    digits = s.substr(2);
                    return 8;
                }
            }
            digits = s;
            return 10;
        }

        static bool parse_u128(std::string_view digits, int base, U128& out)
        {
            out = 0;

            auto val_of = [&](char c) -> int
            {
                if (c >= '0' && c <= '9') return (c - '0');
                if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
                if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
                return -1;
            };

            if (digits.empty())
                return false;

            const U128 maxv = ~static_cast<U128>(0);

            for (char c : digits)
            {
                const int d = val_of(c);
                if (d < 0 || d >= base) return false;

                const U128 before = out;
                const U128 b = static_cast<U128>(base);
                const U128 add = static_cast<U128>(d);

                if (before > (maxv - add) / b)
                    return false;

                out = before * b + add;
            }
            return true;
        }

        static U128 max_unsigned_bits(std::uint32_t bits)
        {
            if (bits >= 128) return ~static_cast<U128>(0);
            return (static_cast<U128>(1) << bits) - static_cast<U128>(1);
        }

        static U128 max_signed_bits(std::uint32_t bits)
        {
            if (bits <= 1) return 0;
            if (bits >= 128) return (static_cast<U128>(1) << 127) - static_cast<U128>(1);
            return (static_cast<U128>(1) << (bits - 1)) - static_cast<U128>(1);
        }

        static bool map_int_kind(kl::rt::IntKind k, std::uint32_t& bits, bool& is_signed)
        {
            using K = kl::rt::IntKind;
            switch (k)
            {
            case K::I8: bits = 8;
                is_signed = true;
                return true;
            case K::I16: bits = 16;
                is_signed = true;
                return true;
            case K::I32: bits = 32;
                is_signed = true;
                return true;
            case K::I64: bits = 64;
                is_signed = true;
                return true;
            case K::I128: bits = 128;
                is_signed = true;
                return true;

            case K::U8: bits = 8;
                is_signed = false;
                return true;
            case K::U16: bits = 16;
                is_signed = false;
                return true;
            case K::U32: bits = 32;
                is_signed = false;
                return true;
            case K::U64: bits = 64;
                is_signed = false;
                return true;
            case K::U128: bits = 128;
                is_signed = false;
                return true;

            default: return false;
            }
        }

        static bool map_float_kind(kl::rt::FloatKind k, bool& is_f32)
        {
            using K = kl::rt::FloatKind;
            switch (k)
            {
            case K::F32: is_f32 = true;
                return true;
            case K::F64: is_f32 = false;
                return true;
            default: return false;
            }
        }

        void record_int(ast::IntLiteralExpr& node, IntLitValue v)
        {
            const auto id = static_cast<std::uint32_t>(out_.ints.size());
            out_.ints.push_back(v);
            out_.int_id.emplace(&node, id);
        }

        void record_float(ast::FloatLiteralExpr& node, FloatLitValue v)
        {
            const auto id = static_cast<std::uint32_t>(out_.floats.size());
            out_.floats.push_back(v);
            out_.float_id.emplace(&node, id);
        }
    };

    void Pass7LiteralLoweringVisitor::visit(ast::ArrayLiteralExpr& a)
    {
        // IMPORTANT: traverse elements, otherwise IntLiteralExpr never gets lowered
        for (auto& ep : a.v_)
        {
            if (ep) ep->accept(*this);
        }
    }


    void Pass7LiteralLoweringVisitor::visit(ast::IntLiteralExpr& i)
    {
        if (out_.int_id.contains(&i))
            return;

        const std::string_view raw = ctx_.numericInterner.view(i.v_);
        const std::string cleaned = strip_underscores(raw);

        std::string_view digits_only{};
        const int base = detect_base(std::string_view{cleaned}, digits_only);

        U128 value = 0;
        if (!parse_u128(digits_only, base, value))
        {
            std::ostringstream oss;
            oss << "invalid integer literal: '" << raw << "'";
            push_diag(out_, Pass7Diagnostic::Code::InvalidIntLiteral, i.location_, oss.str());
            return;
        }

        auto record_by_bits = [&](std::uint32_t bits, bool is_signed)
        {
            if (is_signed)
            {
                if (bits <= 8) record_int(i, static_cast<I8>(value));
                else if (bits <= 16) record_int(i, static_cast<I16>(value));
                else if (bits <= 32) record_int(i, static_cast<I32>(value));
                else if (bits <= 64) record_int(i, static_cast<I64>(value));
                else record_int(i, static_cast<I128>(value));
            }
            else
            {
                if (bits <= 8) record_int(i, static_cast<U8>(value));
                else if (bits <= 16) record_int(i, static_cast<U16>(value));
                else if (bits <= 32) record_int(i, static_cast<U32>(value));
                else if (bits <= 64) record_int(i, static_cast<U64>(value));
                else record_int(i, static_cast<U128>(value));
            }
        };

        if (i.suffix_.has_value())
        {
            std::uint32_t bits = 0;
            bool is_signed = false;

            if (!map_int_kind(*i.suffix_, bits, is_signed))
            {
                push_diag(out_, Pass7Diagnostic::Code::UnsupportedIntSuffix, i.location_,
                          "unsupported integer suffix");
                return;
            }

            const U128 maxv = is_signed ? max_signed_bits(bits) : max_unsigned_bits(bits);
            if (value > maxv)
            {
                push_diag(out_, Pass7Diagnostic::Code::IntOverflow, i.location_,
                          "integer literal overflows requested suffix type");
                return;
            }

            record_by_bits(bits, is_signed);
            return;
        }

        if (value <= max_unsigned_bits(8))
        {
            record_int(i, static_cast<U8>(value));
            return;
        }
        if (value <= max_unsigned_bits(16))
        {
            record_int(i, static_cast<U16>(value));
            return;
        }
        if (value <= max_unsigned_bits(32))
        {
            record_int(i, static_cast<U32>(value));
            return;
        }
        if (value <= max_unsigned_bits(64))
        {
            record_int(i, static_cast<U64>(value));
            return;
        }
        record_int(i, static_cast<U128>(value));
    }

    void Pass7LiteralLoweringVisitor::visit(ast::FloatLiteralExpr& f)
    {
        if (out_.float_id.contains(&f))
            return;

        const std::string_view raw = ctx_.numericInterner.view(f.v_);
        const std::string cleaned = strip_underscores(raw);

        double dv = 0.0;
        {
            std::string tmp(cleaned);
            char* end = nullptr;
            dv = std::strtod(tmp.c_str(), &end);
            if (!end || *end != '\0' || !std::isfinite(dv))
            {
                std::ostringstream oss;
                oss << "invalid float literal: '" << raw << "'";
                push_diag(out_, Pass7Diagnostic::Code::InvalidFloatLiteral, f.location_, oss.str());
                return;
            }
        }

        bool want_f32 = false;
        if (f.suffix_.has_value())
        {
            if (!map_float_kind(*f.suffix_, want_f32))
            {
                push_diag(out_, Pass7Diagnostic::Code::UnsupportedFloatSuffix, f.location_,
                          "unsupported float suffix");
                return;
            }
        }
        else
        {
            want_f32 = false; // default f64
        }

        if (want_f32)
        {
            const auto fv = static_cast<float>(dv);
            if (!std::isfinite(fv))
            {
                push_diag(out_, Pass7Diagnostic::Code::FloatOverflow, f.location_,
                          "float literal overflows f32");
                return;
            }
            const auto id = static_cast<std::uint32_t>(out_.floats.size());
            out_.floats.emplace_back(fv);
            out_.float_id.emplace(&f, id);
        }
        else
        {
            const auto id = static_cast<std::uint32_t>(out_.floats.size());
            out_.floats.emplace_back(dv);
            out_.float_id.emplace(&f, id);
        }
    }

    // ============================================================
    // Pass7 (B): type checking + assignment legality
    // ============================================================

    static bool is_valid_typeid(const Pass5Result& p5, TypeId t)
    {
        return t.value < p5.types.nodes.size();
    }

    struct BuiltinTidCache
    {
        std::unordered_map<BuiltinType, TypeId> map;
    };

    static TypeId builtin_tid(const Pass5Result& p5, BuiltinTidCache& cache, BuiltinType b)
    {
        if (auto it = cache.map.find(b); it != cache.map.end())
            return it->second;

        for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(p5.types.nodes.size()); ++i)
        {
            const TypeNode& n = p5.types.nodes[i];
            if (n.kind == TypeKind::Builtin && n.builtin == b)
            {
                TypeId tid{i};
                cache.map.emplace(b, tid);
                return tid;
            }
        }

        TypeId bad{UINT32_MAX};
        cache.map.emplace(b, bad);
        return bad;
    }

    class Pass7TypeCheckVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass7TypeCheckVisitor(const Pass4Result& p4,
                              Pass5Result& p5,
                              const Pass6Result& p6,
                              const Pass3_5Result* p3_5,
                              Pass7Result& out,
                              std::uint32_t unit_i)
            : p4_(p4), p5_(p5), p6_(p6), p3_5_(p3_5), out_(out), unit_i_(unit_i)
        {
        }

        void visit(ast::Module& m) override;
        void visit(ast::FnDecl& f) override;

        void visit(ast::VarStmt& v) override;
        void visit(ast::AssignExpr& a) override;
        void visit(ast::CallExpr& c) override;

        void visit(ast::IntLiteralExpr& i) override;
        void visit(ast::FloatLiteralExpr& f) override;
        void visit(ast::RefExpr& r) override;
        void visit(ast::UnaryExpr& u) override;
        void visit(ast::BinaryExpr& b) override;
        void visit(ast::IndexExpr& i) override;
        void visit(ast::FieldExpr& f) override;
        void visit(ast::ArrayLiteralExpr& a) override;

    private:
        const Pass4Result& p4_;
        Pass5Result& p5_;
        const Pass6Result& p6_;
        const Pass3_5Result* p3_5_;
        Pass7Result& out_;
        std::uint32_t unit_i_ = 0;

        const ModuleBindings* mb_ = nullptr;
        const FnBindings* fb_ = nullptr;

        BuiltinTidCache builtin_cache_;

        // ------------------------------------------------------------
        // helpers
        // ------------------------------------------------------------

        bool coerce_array_literal_to(TypeId expected, ast::Expr* e)
        {
            auto* al = dynamic_cast<ast::ArrayLiteralExpr*>(e);
            if (!al) return false;

            ArrayInfo ai = as_array_type(expected);
            if (!ai.ok) return false;

            // Assign the array literal the expected type immediately
            set_expr_type(al, expected);

            const auto got = static_cast<std::uint64_t>(al->v_.size());
            const std::uint64_t want = ai.len;

            if (got != want)
            {
                std::ostringstream oss;
                oss << "array literal length mismatch (expected " << want << ", got " << got << ")";
                push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, al->location_, oss.str());
                // keep going to type-check what we can
            }

            const std::uint64_t n = std::min(got, want);

            for (std::uint64_t i = 0; i < n; ++i)
            {
                ast::Expr* el = al->v_[static_cast<size_t>(i)]; // ExprPtr -> raw
                if (!el) continue;

                // Provide element context
                (void)coerce_int_literal_to(ai.elem, el);
                (void)coerce_struct_literal_to(ai.elem, el);
                (void)coerce_array_literal_to(ai.elem, el); // nested arrays

                TypeId et = get_expr_type(el);

                if (!is_valid_typeid(p5_, et) || !is_valid_typeid(p5_, ai.elem))
                {
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, el->location_,
                              "cannot type-check array literal element (unknown type)");
                    continue;
                }

                if (!assignable(ai.elem, et))
                {
                    std::ostringstream oss;
                    oss << "type mismatch in array literal element #" << i
                        << " (expected=" << ai.elem.value << ", got=" << et.value << ")";
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, el->location_, oss.str());
                }
            }

            return true;
        }

        TypeId type_of_typeexpr(ast::TypeExpr* t) const
        {
            if (!t) return TypeId{UINT32_MAX};
            auto it = p5_.type_of.find(t);
            if (it == p5_.type_of.end()) return TypeId{UINT32_MAX};
            return it->second;
        }

        bool is_array_like(TypeId t) const
        {
            if (!is_valid_typeid(p5_, t)) return false;
            const TypeNode& n = p5_.types.nodes[t.value];
            return n.kind == TypeKind::ArrayFixed;
        }

        void set_expr_type(const ast::Expr* e, TypeId t) const
        {
            if (!e) return;
            out_.expr_type.try_emplace(e, t);
        }

        TypeId get_expr_type(ast::Expr* e)
        {
            if (!e) return TypeId{UINT32_MAX};

            if (auto it = out_.expr_type.find(e); it != out_.expr_type.end())
                return it->second;

            e->accept(*this);

            if (auto it2 = out_.expr_type.find(e); it2 != out_.expr_type.end())
                return it2->second;

            return TypeId{UINT32_MAX};
        }

        bool assignable(TypeId dst, TypeId src) const
        {
            if (!is_valid_typeid(p5_, dst) || !is_valid_typeid(p5_, src))
                return false;

            if (dst.value == src.value)
                return true;

            // Allow &mut T -> &T (read-only borrow from mutable borrow)
            const TypeNode& d = p5_.types.nodes[dst.value];
            const TypeNode& s = p5_.types.nodes[src.value];

            if (d.kind == TypeKind::Ref && s.kind == TypeKind::Ref)
            {
                if (d.inner.value == s.inner.value)
                {
                    const bool dst_mut = d.ref_mut;
                    const bool src_mut = s.ref_mut;

                    // destination is immutable ref, source may be mutable ref
                    if (!dst_mut && src_mut)
                        return true;
                }
            }

            return false;
        }

        bool is_struct_like(TypeId t) const
        {
            if (!is_valid_typeid(p5_, t)) return false;
            const TypeNode& n = p5_.types.nodes[t.value];
            return n.kind == TypeKind::Struct || n.kind == TypeKind::ReservedStruct;
        }

        bool coerce_struct_literal_to(TypeId expected, ast::Expr* e) const
        {
            auto* sl = dynamic_cast<ast::StructLiteralExpr*>(e);
            if (!sl) return false;
            if (!is_struct_like(expected)) return false;
            set_expr_type(sl, expected);
            return true;
        }

        // ------------------------------------------------------------
        // find existing interned type ids (Pass5 table)
        // ------------------------------------------------------------

        TypeId intern_ref_tid(TypeId inner, bool mut) const
        {
            if (!is_valid_typeid(p5_, inner)) return TypeId{UINT32_MAX};

            TypeKey k{};
            k.kind = TypeKind::Ref;
            k.inner = inner;
            k.ref_mut = mut;

            return p5_.types.get_or_intern(k);
        }

        TypeId intern_box_tid(TypeId inner) const
        {
            if (!is_valid_typeid(p5_, inner)) return TypeId{UINT32_MAX};

            TypeKey k{};
            k.kind = TypeKind::Box;
            k.inner = inner;

            return p5_.types.get_or_intern(k);
        }

        TypeId intern_array_fixed_tid(TypeId elem, std::uint64_t len) const;

        // ------------------------------------------------------------
        // Type substitution for generic instantiation (interning via find_*)
        // ------------------------------------------------------------
        using SubstMap = std::unordered_map<lex::SymId, TypeId>;

        TypeId instantiate_type(TypeId t, const SubstMap& subst) const
        {
            if (!is_valid_typeid(p5_, t)) return TypeId{UINT32_MAX};

            const TypeNode& n = p5_.types.nodes[t.value];
            switch (n.kind)
            {
            case TypeKind::TypeParam:
                {
                    auto it = subst.find(n.type_param_name);
                    return (it != subst.end()) ? it->second : TypeId{UINT32_MAX};
                }

            case TypeKind::Box:
                {
                    TypeId inner2 = instantiate_type(n.inner, subst);
                    return is_valid_typeid(p5_, inner2) ? intern_box_tid(inner2) : TypeId{UINT32_MAX};
                }

            case TypeKind::Ref:
                {
                    TypeId inner2 = instantiate_type(n.inner, subst);
                    return is_valid_typeid(p5_, inner2) ? intern_ref_tid(inner2, n.ref_mut) : TypeId{UINT32_MAX};
                }

            case TypeKind::ArrayFixed:
                {
                    TypeId elem2 = instantiate_type(n.elem, subst);
                    return is_valid_typeid(p5_, elem2) ? intern_array_fixed_tid(elem2, n.array_len) : TypeId{UINT32_MAX};
                }

            default:
                return t;
            }
        }

        bool instantiate_sig_for_call(FnSig& sig, const ast::CallExpr& c)
        {
            if (sig.type_params.empty())
            {
                if (!c.typeArgs_.empty())
                {
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_,
                              "type arguments were provided but callee is not generic");
                    return false;
                }
                return true;
            }

            const size_t want = sig.type_params.size();
            const size_t got = c.typeArgs_.size();

            if (want != got)
            {
                std::ostringstream oss;
                oss << "wrong number of type arguments (expected " << want << ", got " << got << ")";
                push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_, oss.str());
                return false;
            }

            SubstMap subst;
            subst.reserve(want);

            for (size_t i = 0; i < want; ++i)
            {
                TypeId tid = type_of_typeexpr(c.typeArgs_[i]);
                if (!is_valid_typeid(p5_, tid))
                {
                    std::ostringstream oss;
                    oss << "cannot resolve type argument #" << i;
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_, oss.str());
                    return false;
                }
                subst.emplace(sig.type_params[i], tid);
            }

            for (auto& p : sig.params)
            {
                p = instantiate_type(p, subst);
                if (!is_valid_typeid(p5_, p))
                {
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_,
                              "failed to instantiate generic parameter type");
                    return false;
                }
            }

            sig.ret = instantiate_type(sig.ret, subst);
            if (!is_valid_typeid(p5_, sig.ret))
            {
                push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_,
                          "failed to instantiate generic return type");
                return false;
            }

            return true;
        }

        // ------------------------------------------------------------
        // Ref/Array inspection from Pass5 TypeNode
        // ------------------------------------------------------------
        struct RefInfo
        {
            bool ok = false;
            ast::Mutability mut = ast::Mutability::Imm;
            TypeId pointee{UINT32_MAX};
        };

        struct ArrayInfo
        {
            bool ok = false;
            TypeId elem{UINT32_MAX};
            std::uint64_t len = 0;
        };

        RefInfo as_ref_type(TypeId t) const
        {
            RefInfo ri{};
            if (!is_valid_typeid(p5_, t)) return ri;

            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::Ref)
                return ri;

            ri.ok = true;
            ri.mut = n.ref_mut ? ast::Mutability::Mut : ast::Mutability::Imm;
            ri.pointee = n.inner;
            return ri;
        }

        ArrayInfo as_array_type(TypeId t) const
        {
            ArrayInfo ai{};
            if (!is_valid_typeid(p5_, t)) return ai;

            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::ArrayFixed)
                return ai;

            ai.ok = true;
            ai.elem = n.elem;
            ai.len = n.array_len;
            return ai;
        }

        // ADAPT later if you want field typing in Pass7:
        std::optional<TypeId> struct_field_type(TypeId structTy, lex::SymId fieldName) const
        {
            if (!is_valid_typeid(p5_, structTy)) return std::nullopt;

            const TypeNode& tn = p5_.types.nodes[structTy.value];

            if (tn.kind == TypeKind::Struct)
            {
                auto itLay = p5_.struct_layout.find(tn.struct_id);
                if (itLay == p5_.struct_layout.end()) return std::nullopt;

                const StructLayout& lay = itLay->second;

                auto itIdx = lay.name_to_index.find(fieldName);
                if (itIdx == lay.name_to_index.end()) return std::nullopt;

                const uint32_t idx = itIdx->second;
                if (idx >= lay.field_types_in_order.size()) return std::nullopt;

                TypeId ft = lay.field_types_in_order[idx];
                return is_valid_typeid(p5_, ft) ? std::optional<TypeId>{ft} : std::nullopt;
            }

            // If you have ReservedStruct fields (e.g. Str), handle them here later.
            return std::nullopt;
        }

        // ------------------------------------------------------------
        // binding lookup helpers
        // ------------------------------------------------------------
        const LocalSlotInfo* local_slot_info_of_ref(const ast::RefExpr& r) const
        {
            if (!fb_) return nullptr;
            auto itb = fb_->ref_binding.find(&r);
            if (itb == fb_->ref_binding.end()) return nullptr;

            const Binding& b = itb->second;
            if (b.kind != BindingKind::LocalSlot) return nullptr;

            if (b.slot.index >= fb_->slots.size()) return nullptr;
            return &fb_->slots[b.slot.index];
        }

        // ------------------------------------------------------------
        // lvalue/place analysis for assignment lhs
        // ------------------------------------------------------------
        struct PlaceResult
        {
            bool is_place = false;
            bool is_mutable = false;
            TypeId type{UINT32_MAX};
            lex::Loc loc{};
        };

        PlaceResult analyze_place(ast::Expr* e)
        {
            PlaceResult pr{};
            if (!e) return pr;
            pr.loc = e->location_;
            pr.type = get_expr_type(e);

            if (auto* r = dynamic_cast<ast::RefExpr*>(e))
            {
                const LocalSlotInfo* si = local_slot_info_of_ref(*r);
                if (!si)
                    return pr;

                pr.is_place = true;
                pr.is_mutable = (si->mut_ == ast::Mutability::Mut);
                pr.type = get_expr_type(r);
                return pr;
            }

            if (auto* u = dynamic_cast<ast::UnaryExpr*>(e))
            {
                if (u->op == ast::UnaryOp::deref)
                {
                    TypeId ot = get_expr_type(u->expr_);
                    RefInfo ri = as_ref_type(ot);

                    pr.is_place = ri.ok;
                    pr.is_mutable = ri.ok && (ri.mut == ast::Mutability::Mut);
                    pr.type = ri.ok ? ri.pointee : TypeId{UINT32_MAX};
                    return pr;
                }
            }

            if (auto* ix = dynamic_cast<ast::IndexExpr*>(e))
            {
                PlaceResult base = analyze_place(ix->base_);
                if (!base.is_place)
                    return pr;

                TypeId bt = get_expr_type(ix->base_);
                ArrayInfo ai = as_array_type(bt);

                pr.is_place = true;
                pr.is_mutable = base.is_mutable;
                pr.type = ai.ok ? ai.elem : TypeId{UINT32_MAX};
                return pr;
            }

            if (auto* fe = dynamic_cast<ast::FieldExpr*>(e))
            {
                PlaceResult base = analyze_place(fe->base_);
                if (!base.is_place)
                    return pr;

                TypeId bt = get_expr_type(fe->base_);
                if (auto ft = struct_field_type(bt, fe->field); ft.has_value())
                    pr.type = *ft;
                else
                    pr.type = TypeId{UINT32_MAX};

                pr.is_place = true;
                pr.is_mutable = base.is_mutable;
                return pr;
            }

            return pr;
        }

        // ------------------------------------------------------------
        // call signature helper
        // ------------------------------------------------------------
        ast::FnDecl* find_user_fn_decl(FnId id) const
        {
            for (const ModuleGlobals& mg : p4_.modules)
                for (const FnSym& fs : mg.fns)
                    if (fs.id == id) return fs.decl;
            return nullptr;
        }

        ast::LoadFnDecl* find_user_load_fn_decl(LoadFnId id) const
        {
            for (const ModuleGlobals& mg : p4_.modules)
                for (const LoadFnSym& ls : mg.load_fns)
                    if (ls.id == id) return ls.decl;
            return nullptr;
        }

        const Binding* binding_of_callee(ast::Expr* callee) const
        {
            if (auto* r = dynamic_cast<ast::RefExpr*>(callee))
            {
                auto it = fb_->ref_binding.find(r);
                if (it != fb_->ref_binding.end())
                    return &it->second;
            }

            auto it2 = fb_->expr_binding.find(callee);
            if (it2 != fb_->expr_binding.end())
                return &it2->second;

            return nullptr;
        }

        std::optional<lex::SymId> callee_leaf_name(ast::Expr* callee) const
        {
            if (auto* r = dynamic_cast<ast::RefExpr*>(callee))
                return r->name;

            if (auto* p = dynamic_cast<ast::PathExpr*>(callee))
            {
                if (!p->path_.empty())
                    return p->path_.back();
                return std::nullopt;
            }

            return std::nullopt;
        }

        FnSig signature_of_callee(ast::Expr* callee) const
        {
            FnSig sig{};
            if (!callee || !fb_)
                return sig;

            const Binding* pb = binding_of_callee(callee);
            if (!pb)
                return sig;

            const Binding& b = *pb;
            const auto leafNameOpt = callee_leaf_name(callee);

            // Treat RuntimeIntrinsic as callable *only* if we have a reserved prototype in p3_5_.
            auto try_reserved_sig_by_name = [&]() -> bool
            {
                if (!p3_5_ || !leafNameOpt.has_value())
                    return false;

                auto it = p3_5_->sigs.fns.find(*leafNameOpt);
                if (it == p3_5_->sigs.fns.end())
                    return false;

                ast::FnDecl* fd = it->second;
                if (!fd) return false;

                sig.type_params.clear();
                sig.type_params.reserve(fd->typeParamsDecls_.size());
                for (auto* tp : fd->typeParamsDecls_)
                    if (tp) sig.type_params.push_back(tp->name_);

                sig.params.clear();
                sig.params.reserve(fd->params_.size());
                for (auto* p : fd->params_)
                    sig.params.push_back(type_of_typeexpr(p ? p->type_ : nullptr));

                sig.ret = type_of_typeexpr(fd->ret_);
                sig.ok = true;
                return true;
            };

            if (b.kind == BindingKind::GlobalFn)
            {
                // Reserved/builtin fast-path by name (important because reserved fns may not exist in Pass4 modules)
                if (try_reserved_sig_by_name())
                    return sig;

                // Fallback: locate user decl by FnId
                ast::FnDecl* fd = find_user_fn_decl(b.fn);
                if (!fd) return sig;

                sig.type_params.clear();
                sig.type_params.reserve(fd->typeParamsDecls_.size());
                for (auto* tp : fd->typeParamsDecls_)
                    if (tp) sig.type_params.push_back(tp->name_);

                sig.params.clear();
                sig.params.reserve(fd->params_.size());
                for (auto* p : fd->params_)
                    sig.params.push_back(type_of_typeexpr(p ? p->type_ : nullptr));

                sig.ret = type_of_typeexpr(fd->ret_);
                sig.ok = true;
                return sig;
            }

            if (b.kind == BindingKind::GlobalLoadFn)
            {
                ast::LoadFnDecl* ld = find_user_load_fn_decl(b.load_fn);
                if (!ld) return sig;

                sig.type_params.clear();

                sig.params.clear();
                sig.params.reserve(ld->params_.size());
                for (auto* p : ld->params_)
                    sig.params.push_back(type_of_typeexpr(p ? p->type_ : nullptr));

                sig.ret = type_of_typeexpr(ld->ret_);
                sig.ok = true;
                return sig;
            }

            if (b.kind == BindingKind::RuntimeIntrinsic)
            {
                // In your pipeline, you can either:
                //  - bind reserved names as GlobalFn (via Pass4.5 injected IDs), OR
                //  - bind them as RuntimeIntrinsic.
                // Pass7 supports both, but RuntimeIntrinsic requires the reserved prototype from Pass3.5.
                if (try_reserved_sig_by_name())
                    return sig;

                return sig; // not ok
            }

            return sig;
        }

        // ------------------------------------------------------------
        // builtins + literal coercion
        // ------------------------------------------------------------
        std::optional<BuiltinType> builtin_of(TypeId t) const
        {
            if (!is_valid_typeid(p5_, t)) return std::nullopt;
            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::Builtin) return std::nullopt;
            return n.builtin;
        }

        static bool builtin_int_info(BuiltinType b, std::uint32_t& bits, bool& is_signed)
        {
            switch (b)
            {
            case BuiltinType::I8: bits = 8;
                is_signed = true;
                return true;
            case BuiltinType::I16: bits = 16;
                is_signed = true;
                return true;
            case BuiltinType::I32: bits = 32;
                is_signed = true;
                return true;
            case BuiltinType::I64: bits = 64;
                is_signed = true;
                return true;
            case BuiltinType::I128: bits = 128;
                is_signed = true;
                return true;

            case BuiltinType::U8: bits = 8;
                is_signed = false;
                return true;
            case BuiltinType::U16: bits = 16;
                is_signed = false;
                return true;
            case BuiltinType::U32: bits = 32;
                is_signed = false;
                return true;
            case BuiltinType::U64: bits = 64;
                is_signed = false;
                return true;
            case BuiltinType::U128: bits = 128;
                is_signed = false;
                return true;

            default: return false;
            }
        }

        static U128 lit_magnitude_u128(const IntLitValue& v)
        {
            return std::visit([](auto x) -> U128 { return static_cast<U128>(x); }, v);
        }

        static U128 max_unsigned_bits(std::uint32_t bits)
        {
            if (bits >= 128) return ~static_cast<U128>(0);
            return (static_cast<U128>(1) << bits) - static_cast<U128>(1);
        }

        static U128 max_signed_bits(std::uint32_t bits)
        {
            if (bits <= 1) return 0;
            if (bits >= 128) return (static_cast<U128>(1) << 127) - static_cast<U128>(1);
            return (static_cast<U128>(1) << (bits - 1)) - static_cast<U128>(1);
        }

        bool coerce_int_literal_to(TypeId expected, ast::Expr* e)
        {
            auto* il = dynamic_cast<ast::IntLiteralExpr*>(e);
            if (!il) return false;

            auto it = out_.int_id.find(il);
            if (it == out_.int_id.end()) return false;

            const auto b = builtin_of(expected);
            if (!b.has_value()) return false;

            std::uint32_t bits = 0;
            bool is_signed = false;
            if (!builtin_int_info(*b, bits, is_signed)) return false;

            const IntLitValue& cur = out_.ints[it->second];
            const U128 mag = lit_magnitude_u128(cur);

            const U128 maxv = is_signed ? max_signed_bits(bits) : max_unsigned_bits(bits);
            if (mag > maxv)
            {
                push_diag(out_, Pass7Diagnostic::Code::IntOverflow, il->location_,
                          "integer literal does not fit expected type");
                return false;
            }

            if (is_signed)
            {
                if (bits <= 8) out_.ints[it->second] = static_cast<I8>(mag);
                else if (bits <= 16) out_.ints[it->second] = static_cast<I16>(mag);
                else if (bits <= 32) out_.ints[it->second] = static_cast<I32>(mag);
                else if (bits <= 64) out_.ints[it->second] = static_cast<I64>(mag);
                else out_.ints[it->second] = static_cast<I128>(mag);
            }
            else
            {
                if (bits <= 8) out_.ints[it->second] = static_cast<U8>(mag);
                else if (bits <= 16) out_.ints[it->second] = static_cast<U16>(mag);
                else if (bits <= 32) out_.ints[it->second] = static_cast<U32>(mag);
                else if (bits <= 64) out_.ints[it->second] = static_cast<U64>(mag);
                else out_.ints[it->second] = static_cast<U128>(mag);
            }

            set_expr_type(il, expected);
            return true;
        }
    };

    // ------------------------------------------------------------
    // Visitor wiring
    // ------------------------------------------------------------

    void Pass7TypeCheckVisitor::visit(ast::Module& m)
    {
        mb_ = (unit_i_ < p6_.modules.size()) ? &p6_.modules[unit_i_] : nullptr;
        fb_ = nullptr;

        ast::visitor::OverallVisitor::visit(m);

        mb_ = nullptr;
        fb_ = nullptr;
    }

    void Pass7TypeCheckVisitor::visit(ast::FnDecl& f)
    {
        fb_ = nullptr;

        if (mb_)
        {
            for (const auto& b : mb_->fns | std::views::values)
            {
                if (b.decl == &f)
                {
                    fb_ = &b;
                    break;
                }
            }
        }

        ast::visitor::OverallVisitor::visit(f);
        fb_ = nullptr;
    }

    // ------------------------------------------------------------
    // Expression typing
    // ------------------------------------------------------------

    void Pass7TypeCheckVisitor::visit(ast::IntLiteralExpr& i)
    {
        auto it = out_.int_id.find(&i);
        if (it == out_.int_id.end())
        {
            set_expr_type(&i, TypeId{UINT32_MAX});
            return;
        }

        const IntLitValue& v = out_.ints[it->second];
        TypeId t{UINT32_MAX};

        if (std::holds_alternative<I8>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::I8);
        else if (std::holds_alternative<I16>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::I16);
        else if (std::holds_alternative<I32>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::I32);
        else if (std::holds_alternative<I64>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::I64);
        else if (std::holds_alternative<I128>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::I128);
        else if (std::holds_alternative<U8>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::U8);
        else if (std::holds_alternative<U16>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::U16);
        else if (std::holds_alternative<U32>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::U32);
        else if (std::holds_alternative<U64>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::U64);
        else t = builtin_tid(p5_, builtin_cache_, BuiltinType::U128);

        set_expr_type(&i, t);
    }

    void Pass7TypeCheckVisitor::visit(ast::FloatLiteralExpr& f)
    {
        auto it = out_.float_id.find(&f);
        if (it == out_.float_id.end())
        {
            set_expr_type(&f, TypeId{UINT32_MAX});
            return;
        }

        const FloatLitValue& v = out_.floats[it->second];
        TypeId t = TypeId{UINT32_MAX};
        if (std::holds_alternative<F32>(v)) t = builtin_tid(p5_, builtin_cache_, BuiltinType::F32);
        else t = builtin_tid(p5_, builtin_cache_, BuiltinType::F64);

        set_expr_type(&f, t);
    }

    void Pass7TypeCheckVisitor::visit(ast::RefExpr& r)
    {
        if (!fb_)
        {
            set_expr_type(&r, TypeId{UINT32_MAX});
            return;
        }

        auto itb = fb_->ref_binding.find(&r);
        if (itb == fb_->ref_binding.end())
        {
            set_expr_type(&r, TypeId{UINT32_MAX});
            return;
        }

        const Binding& b = itb->second;

        if (b.kind == BindingKind::LocalSlot)
        {
            if (b.slot.index >= fb_->slots.size())
            {
                set_expr_type(&r, TypeId{UINT32_MAX});
                return;
            }

            const LocalSlotInfo& si = fb_->slots[b.slot.index];

            ast::TypeExpr* texpr = nullptr;
            if (si.var_decl) texpr = si.var_decl->type_;
            if (si.param_decl) texpr = si.param_decl->type_;

            set_expr_type(&r, type_of_typeexpr(texpr));
            return;
        }

        // Using fn/load-fn/import-alias as a value is not a typed expression in this language.
        set_expr_type(&r, TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::UnaryExpr& u)
    {
        if (u.expr_) u.expr_->accept(*this);

        TypeId ot = get_expr_type(u.expr_);
        TypeId outT{UINT32_MAX};

        switch (u.op)
        {
        case ast::UnaryOp::logical_not:
            outT = builtin_tid(p5_, builtin_cache_, BuiltinType::Bool);
            break;

        case ast::UnaryOp::deref:
            {
                RefInfo ri = as_ref_type(ot);
                outT = ri.ok ? ri.pointee : TypeId{UINT32_MAX};
                break;
            }

        case ast::UnaryOp::addr_of:
            {
                PlaceResult pr = analyze_place(u.expr_);
                if (!pr.is_place || !is_valid_typeid(p5_, pr.type))
                {
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, u.location_,
                              "cannot take address-of non-place expression");
                    outT = TypeId{UINT32_MAX};
                    break;
                }
                outT = intern_ref_tid(pr.type, /*mut=*/false);
                break;
            }

        case ast::UnaryOp::addr_of_mut:
            {
                PlaceResult pr = analyze_place(u.expr_);
                if (!pr.is_place || !is_valid_typeid(p5_, pr.type))
                {
                    push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, u.location_,
                              "cannot take &mut of non-place expression");
                    outT = TypeId{UINT32_MAX};
                    break;
                }
                if (!pr.is_mutable)
                {
                    push_diag(out_, Pass7Diagnostic::Code::ImmutableAssign, u.location_,
                              "cannot take &mut of immutable place");
                    outT = TypeId{UINT32_MAX};
                    break;
                }
                outT = intern_ref_tid(pr.type, /*mut=*/true); // IMPORTANT: mut=true
                break;
            }

        case ast::UnaryOp::negation:
        case ast::UnaryOp::preincrement:
        case ast::UnaryOp::predecrement:
        case ast::UnaryOp::postincrement:
        case ast::UnaryOp::postdecrement:
            outT = ot;
            break;

        default:
            outT = TypeId{UINT32_MAX};
            break;
        }

        if (!is_valid_typeid(p5_, outT) &&
            (u.op == ast::UnaryOp::addr_of || u.op == ast::UnaryOp::addr_of_mut))
        {
            push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, u.location_,
                      "cannot form reference type: missing &T / &mut T in type table (Pass5)");
        }

        set_expr_type(&u, outT);
    }

    void Pass7TypeCheckVisitor::visit(ast::BinaryExpr& b)
    {
        if (b.lhs_) b.lhs_->accept(*this);
        if (b.rhs_) b.rhs_->accept(*this);

        TypeId lt = get_expr_type(b.lhs_);
        TypeId rt = get_expr_type(b.rhs_);

        TypeId outT{UINT32_MAX};

        switch (b.op)
        {
        case ast::BinaryOp::logical_and:
        case ast::BinaryOp::logical_or:
            outT = builtin_tid(p5_, builtin_cache_, BuiltinType::Bool);
            break;

        case ast::BinaryOp::equal:
        case ast::BinaryOp::not_equal:
        case ast::BinaryOp::less:
        case ast::BinaryOp::less_equal:
        case ast::BinaryOp::greater:
        case ast::BinaryOp::greater_equal:
            if (is_valid_typeid(p5_, lt) && is_valid_typeid(p5_, rt) && lt.value == rt.value)
                outT = builtin_tid(p5_, builtin_cache_, BuiltinType::Bool);
            break;

        case ast::BinaryOp::add:
        case ast::BinaryOp::subtract:
        case ast::BinaryOp::multiply:
        case ast::BinaryOp::divide:
        case ast::BinaryOp::modulo:
            if (is_valid_typeid(p5_, lt) && is_valid_typeid(p5_, rt) && lt.value == rt.value)
                outT = lt;
            break;

        default:
            break;
        }

        set_expr_type(&b, outT);
    }

    void Pass7TypeCheckVisitor::visit(ast::IndexExpr& i)
    {
        if (i.base_) i.base_->accept(*this);
        if (i.index_) i.index_->accept(*this);

        TypeId bt = get_expr_type(i.base_);
        ArrayInfo ai = as_array_type(bt);

        set_expr_type(&i, ai.ok ? ai.elem : TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::FieldExpr& f)
    {
        if (f.base_) f.base_->accept(*this);

        TypeId bt = get_expr_type(f.base_);
        if (auto ft = struct_field_type(bt, f.field); ft.has_value())
            set_expr_type(&f, *ft);
        else
            set_expr_type(&f, TypeId{UINT32_MAX});
    }

    // ------------------------------------------------------------
    // Statement / check logic
    // ------------------------------------------------------------

    void Pass7TypeCheckVisitor::visit(ast::VarStmt& v)
    {
        // Do NOT call OverallVisitor first: it would visit init_ before we can provide context.

        // Still visit other children if you have them (rare for VarStmt). Typically only init_ matters.

        if (!v.type_ || !v.init_)
            return;

        const TypeId dst = type_of_typeexpr(v.type_);

        // Provide context BEFORE any visit of the initializer.
        (void)coerce_array_literal_to(dst, v.init_);
        (void)coerce_int_literal_to(dst, v.init_);
        (void)coerce_struct_literal_to(dst, v.init_);

        const TypeId src = get_expr_type(v.init_); // this will visit lazily

        if (!is_valid_typeid(p5_, dst) || !is_valid_typeid(p5_, src))
        {
            push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, v.location_,
                      "cannot type-check initializer (unknown type)");
            return;
        }

        if (!assignable(dst, src))
        {
            std::ostringstream oss;
            oss << "type mismatch in initializer (dst=" << dst.value << ", src=" << src.value << ")";
            push_diag(out_, Pass7Diagnostic::Code::TypeMismatchInit, v.location_, oss.str());
        }
    }

    void Pass7TypeCheckVisitor::visit(ast::AssignExpr& a)
    {
        if (a.lhs_) a.lhs_->accept(*this);
        if (a.rhs_) a.rhs_->accept(*this);

        PlaceResult pr = analyze_place(a.lhs_);
        if (!pr.is_place)
        {
            push_diag(out_, Pass7Diagnostic::Code::NonAssignableLhs, a.location_,
                      "left-hand side of assignment is not assignable");
        }
        else if (!pr.is_mutable)
        {
            push_diag(out_, Pass7Diagnostic::Code::ImmutableAssign, a.location_,
                      "cannot assign to immutable place");
        }

        const TypeId dst = get_expr_type(a.lhs_);

        (void)coerce_int_literal_to(dst, a.rhs_);
        (void)coerce_struct_literal_to(dst, a.rhs_);
        (void)coerce_array_literal_to(dst, a.rhs_);

        const TypeId src = get_expr_type(a.rhs_);

        if (!is_valid_typeid(p5_, dst) || !is_valid_typeid(p5_, src))
        {
            push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, a.location_,
                      "cannot type-check assignment (unknown type)");
            return;
        }

        if (!assignable(dst, src))
        {
            std::ostringstream oss;
            oss << "type mismatch in assignment (dst=" << dst.value << ", src=" << src.value << ")";
            push_diag(out_, Pass7Diagnostic::Code::TypeMismatchAssign, a.location_, oss.str());
        }

        set_expr_type(&a, dst);
    }

    void Pass7TypeCheckVisitor::visit(ast::ArrayLiteralExpr& a)
    {
        for (auto& ep : a.v_)
            if (ep) ep->accept(*this);

        // If already typed by contextual coercion, do nothing.
        auto it = out_.expr_type.find(&a);
        if (it != out_.expr_type.end() && is_valid_typeid(p5_, it->second))
            return;

        // No context: cannot infer reliably (keep language rule simple)
        push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, a.location_,
                  "cannot infer array element type (unknown element type)");
        set_expr_type(&a, TypeId{UINT32_MAX});
    }

    TypeId Pass7TypeCheckVisitor::intern_array_fixed_tid(TypeId elem, std::uint64_t len) const
    {
        if (!is_valid_typeid(p5_, elem)) return TypeId{UINT32_MAX};

        TypeKey k{};
        k.kind = TypeKind::ArrayFixed;
        k.elem = elem;
        k.array_len = len;

        return p5_.types.get_or_intern(k);
    }


    // ============================================================
    // FIXED: CallExpr typing (works for user fns, load fns, and reserved/builtin fns via Pass3.5)
    // ============================================================

    void Pass7TypeCheckVisitor::visit(ast::CallExpr& c)
    {
        // 1) Visit children first (so arg expr types exist)
        if (c.callee_) c.callee_->accept(*this);
        for (auto* a : c.args_)
            if (a) a->accept(*this);

        // 2) Resolve signature from Pass6 binding (RefExpr or PathExpr)
        FnSig sig = signature_of_callee(c.callee_);
        if (!sig.ok)
        {
            push_diag(out_, Pass7Diagnostic::Code::NonCallableCallee, c.location_,
                      "callee is not callable (expected fn or load fn)");
            set_expr_type(&c, TypeId{UINT32_MAX});
            return;
        }

        // 3) Instantiate generics using explicit type arguments
        if (!instantiate_sig_for_call(sig, c))
        {
            set_expr_type(&c, TypeId{UINT32_MAX});
            return;
        }

        // 4) Arity check
        if (c.args_.size() != sig.params.size())
        {
            std::ostringstream oss;
            oss << "wrong number of arguments (expected " << sig.params.size()
                << ", got " << c.args_.size() << ")";
            push_diag(out_, Pass7Diagnostic::Code::WrongArgCount, c.location_, oss.str());
            set_expr_type(&c, sig.ret);
            return;
        }

        // 5) Per-arg type check + literal coercions
        for (size_t i = 0; i < c.args_.size(); ++i)
        {
            TypeId pt = sig.params[i];

            (void)coerce_int_literal_to(pt, c.args_[i]);
            (void)coerce_struct_literal_to(pt, c.args_[i]);
            (void)coerce_array_literal_to(pt, c.args_[i]);

            TypeId at = get_expr_type(c.args_[i]);

            if (!is_valid_typeid(p5_, at) || !is_valid_typeid(p5_, pt))
            {
                push_diag(out_, Pass7Diagnostic::Code::UnknownExprType, c.location_,
                          "cannot type-check call (unknown arg/param type)");
                continue;
            }

            if (!assignable(pt, at))
            {
                std::ostringstream oss;
                oss << "type mismatch in call arg #" << i
                    << " (param=" << pt.value << ", arg=" << at.value << ")";
                const lex::Loc loc = c.args_[i] ? c.args_[i]->location_ : c.location_;
                push_diag(out_, Pass7Diagnostic::Code::TypeMismatchCallArg, loc, oss.str());
            }
        }

        set_expr_type(&c, sig.ret);
    }

    // ============================================================
    // Pass7 driver
    // ============================================================

    Pass7Result run_pass7(const Translation& tr,
                          const CompilerContext& ctx,
                          const Pass4Result& p4,
                          Pass5Result& p5,
                          const Pass6Result& p6,
                          const Pass3_5Result* p3_5)
    {
        Pass7Result out{};

        // (1) literal lowering
        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass7LiteralLoweringVisitor vis(ctx, out);
            m->accept(vis);
        }

        // (2) type checking + assignment legality
        for (std::uint32_t unit_i = 0; unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m) continue;

            Pass7TypeCheckVisitor tcv(p4, p5, p6, p3_5, out, unit_i);
            m->accept(tcv);
        }

        return out;
    }
} // namespace sema
