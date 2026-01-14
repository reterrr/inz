// ============================================================================
// pass7.cpp
// ============================================================================

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

#include "expr/array_literal_expr.hpp"
#include "expr/assign_expr.hpp"
#include "expr/binary_op_expr.hpp"
#include "expr/call_expr.hpp"
#include "expr/field_expr.hpp"
#include "expr/index_expr.hpp"
#include "expr/path_expr.hpp"
#include "expr/struct_literal_expr.hpp"
#include "expr/unary_op_expr.hpp"
#include "stmt/var_statement.hpp"

namespace sema
{
    static thread_local ModuleId g_pass7_unit_module = kInvalidModuleId;

    static constexpr std::vector<lex::SymId> kPass7EmptyPath{};
    static thread_local const std::vector<lex::SymId>* g_pass7_unit_path = &kPass7EmptyPath;

    struct Pass7UnitModuleScope final
    {
        ModuleId prev_mid{};
        const std::vector<lex::SymId>* prev_path = &kPass7EmptyPath;

        Pass7UnitModuleScope(ModuleId m, const std::vector<lex::SymId>* path)
            : prev_mid(g_pass7_unit_module), prev_path(g_pass7_unit_path)
        {
            g_pass7_unit_module = m;
            g_pass7_unit_path = (path ? path : &kPass7EmptyPath);
        }

        ~Pass7UnitModuleScope()
        {
            g_pass7_unit_module = prev_mid;
            g_pass7_unit_path = prev_path;
        }
    };

    static std::string pass7_module_prefix()
    {
        std::ostringstream oss;
        oss << "pass7[m=" << g_pass7_unit_module.value << "]: ";
        return oss.str();
    }

    static inline void pass7_log_begin(LogSequence& logs, const lex::Loc& loc)
    {
        log_path(logs, *g_pass7_unit_path, loc, /*also_log_idents=*/false);
    }

    static inline void pass7_log_text(LogSequence& logs, const lex::Loc& loc, std::string msg)
    {
        pass7_log_begin(logs, loc);
        log_msg(logs, std::move(msg));
    }

    static inline void pass7_log_ident_err(LogSequence& logs,
                                           const lex::Loc& loc,
                                           std::string msg,
                                           lex::SymId id)
    {
        pass7_log_begin(logs, loc);
        log_msg(logs, std::move(msg));
        log_ident(logs, id, loc);
    }

    static inline void pass7_log_numeric_err(LogSequence& logs,
                                             const lex::Loc& loc,
                                             std::string msg,
                                             lex::SymId id)
    {
        pass7_log_begin(logs, loc);
        log_msg(logs, std::move(msg));
        log_numeric(logs, id, loc);
    }

    static inline void pass7_log_path_err(LogSequence& logs,
                                          const lex::Loc& loc,
                                          std::string msg,
                                          const std::vector<lex::SymId>& path)
    {
        pass7_log_begin(logs, loc);
        log_msg(logs, std::move(msg));
        log_path(logs, path, loc, /*also_log_idents=*/false);
    }


    // =========================================================================
    // Pass7 literal lowering
    // =========================================================================

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
        void visit(ast::CharLiteralExpr&) override;

    private:
        const CompilerContext& ctx_;
        Pass7Result& out_;

        static std::string strip_underscores(std::string_view s)
        {
            std::string out;
            out.reserve(s.size());
            for (char c : s)
            {
                if (c == '_')
                    continue;
                out.push_back(c);
            }
            return out;
        }

        void record_char(ast::CharLiteralExpr& node, CharLitValue v)
        {
            const auto id = static_cast<std::uint32_t>(out_.chars.size());
            out_.chars.push_back(v);
            out_.char_id.emplace(&node, id);
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
                if (c >= '0' && c <= '9')
                    return (c - '0');
                if (c >= 'a' && c <= 'f')
                    return 10 + (c - 'a');
                if (c >= 'A' && c <= 'F')
                    return 10 + (c - 'A');
                return -1;
            };

            if (digits.empty())
                return false;

            const U128 maxv = ~static_cast<U128>(0);

            for (char c : digits)
            {
                const int d = val_of(c);
                if (d < 0 || d >= base)
                    return false;

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
            if (bits >= 128)
                return ~static_cast<U128>(0);
            return (static_cast<U128>(1) << bits) - static_cast<U128>(1);
        }

        static U128 max_signed_bits(std::uint32_t bits)
        {
            if (bits <= 1)
                return 0;
            if (bits >= 128)
                return (static_cast<U128>(1) << 127) - static_cast<U128>(1);
            return (static_cast<U128>(1) << (bits - 1)) - static_cast<U128>(1);
        }

        static bool map_int_kind(kl::rt::IntKind k, std::uint32_t& bits, bool& is_signed)
        {
            using K = kl::rt::IntKind;
            switch (k)
            {
            case K::I8: bits = 8; is_signed = true; return true;
            case K::I16: bits = 16; is_signed = true; return true;
            case K::I32: bits = 32; is_signed = true; return true;
            case K::I64: bits = 64; is_signed = true; return true;
            case K::I128: bits = 128; is_signed = true; return true;

            case K::U8: bits = 8; is_signed = false; return true;
            case K::U16: bits = 16; is_signed = false; return true;
            case K::U32: bits = 32; is_signed = false; return true;
            case K::U64: bits = 64; is_signed = false; return true;
            case K::U128: bits = 128; is_signed = false; return true;

            default:
                return false;
            }
        }

        static bool map_float_kind(kl::rt::FloatKind k, bool& is_f32)
        {
            using K = kl::rt::FloatKind;
            switch (k)
            {
            case K::F32: is_f32 = true; return true;
            case K::F64: is_f32 = false; return true;
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
        for (auto& ep : a.v_)
        {
            if (ep)
                ep->accept(*this);
        }
    }

    void Pass7LiteralLoweringVisitor::visit(ast::CharLiteralExpr& ch)
    {
        if (out_.char_id.contains(&ch))
            return;

        const CharLitValue v = ch.v_;
        record_char(ch, v);
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
            pass7_log_numeric_err(out_.errors,
                                  i.location_,
                                  pass7_module_prefix() + "InvalidIntLiteral: invalid integer literal",
                                  i.v_);
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
                pass7_log_numeric_err(out_.errors,
                                      i.location_,
                                      pass7_module_prefix() + "UnsupportedIntSuffix: unsupported integer suffix",
                                      i.v_);
                return;
            }

            const U128 maxv = is_signed ? max_signed_bits(bits) : max_unsigned_bits(bits);
            if (value > maxv)
            {
                pass7_log_numeric_err(out_.errors,
                                      i.location_,
                                      pass7_module_prefix()
                                      + "IntOverflow: integer literal overflows requested suffix type",
                                      i.v_);
                return;
            }

            record_by_bits(bits, is_signed);
            return;
        }

        if (value <= max_unsigned_bits(8))  { record_int(i, static_cast<U8>(value));  return; }
        if (value <= max_unsigned_bits(16)) { record_int(i, static_cast<U16>(value)); return; }
        if (value <= max_unsigned_bits(32)) { record_int(i, static_cast<U32>(value)); return; }
        if (value <= max_unsigned_bits(64)) { record_int(i, static_cast<U64>(value)); return; }

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
                pass7_log_numeric_err(out_.errors,
                                      f.location_,
                                      pass7_module_prefix() + "InvalidFloatLiteral: invalid float literal",
                                      f.v_);
                return;
            }
        }

        bool want_f32 = false;
        if (f.suffix_.has_value())
        {
            if (!map_float_kind(*f.suffix_, want_f32))
            {
                pass7_log_numeric_err(out_.errors,
                                      f.location_,
                                      pass7_module_prefix() + "UnsupportedFloatSuffix: unsupported float suffix",
                                      f.v_);
                return;
            }
        }
        else
        {
            want_f32 = false;
        }

        if (want_f32)
        {
            const auto fv = static_cast<float>(dv);
            if (!std::isfinite(fv))
            {
                pass7_log_numeric_err(out_.errors,
                                      f.location_,
                                      pass7_module_prefix() + "FloatOverflow: float literal overflows f32",
                                      f.v_);
                return;
            }
            record_float(f, static_cast<F32>(fv));
        }
        else
        {
            record_float(f, static_cast<F64>(dv));
        }
    }


    // =========================================================================
    // Pass7 type checking
    // =========================================================================

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
        void visit(ast::ReturnStatement& r) override;
        void visit(ast::BoolLiteralExpr& b) override;

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
        void visit(ast::CharLiteralExpr& c) override;

    private:
        const Pass4Result& p4_;
        Pass5Result& p5_;
        const Pass6Result& p6_;
        const Pass3_5Result* p3_5_;
        Pass7Result& out_;
        std::uint32_t unit_i_ = 0;
        TypeId cur_fn_ret_{UINT32_MAX};
        lex::Loc cur_fn_loc_{};

        const ModuleBindings* mb_ = nullptr;
        const FnBindings* fb_ = nullptr;

        BuiltinTidCache builtin_cache_;

        void set_expr_type(const ast::Expr* e, TypeId t) const
        {
            if (!e)
                return;
            out_.expr_type.try_emplace(e, t);
        }

        TypeId get_expr_type(ast::Expr* e)
        {
            if (!e)
                return TypeId{UINT32_MAX};

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

            const TypeNode& d = p5_.types.nodes[dst.value];
            const TypeNode& s = p5_.types.nodes[src.value];

            if (d.kind == TypeKind::Ref && s.kind == TypeKind::Ref)
            {
                if (d.inner.value == s.inner.value)
                {
                    const bool dst_mut = d.ref_mut;
                    const bool src_mut = s.ref_mut;
                    if (!dst_mut && src_mut)
                        return true;
                }
            }

            return false;
        }

        TypeId type_of_typeexpr(ast::TypeExpr* t) const
        {
            if (!t)
                return TypeId{UINT32_MAX};
            auto it = p5_.type_of.find(t);
            if (it == p5_.type_of.end())
                return TypeId{UINT32_MAX};
            return it->second;
        }

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

        // NEW: Box<T> treated as runtime array of T
        struct DynArrayInfo
        {
            bool ok = false;
            TypeId elem{UINT32_MAX}; // T in Box<T>
        };

        RefInfo as_ref_type(TypeId t) const
        {
            RefInfo ri{};
            if (!is_valid_typeid(p5_, t))
                return ri;

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
            if (!is_valid_typeid(p5_, t))
                return ai;

            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::ArrayFixed)
                return ai;

            ai.ok = true;
            ai.elem = n.elem;
            ai.len = n.array_len;
            return ai;
        }

        DynArrayInfo as_dyn_array_type(TypeId t) const
        {
            DynArrayInfo di{};
            if (!is_valid_typeid(p5_, t))
                return di;

            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::Box)
                return di;

            di.ok = true;
            di.elem = n.inner;
            return di;
        }

        bool is_struct_like(TypeId t) const
        {
            if (!is_valid_typeid(p5_, t))
                return false;
            const TypeNode& n = p5_.types.nodes[t.value];
            return n.kind == TypeKind::Struct || n.kind == TypeKind::ReservedStruct;
        }

        bool coerce_struct_literal_to(TypeId expected, ast::Expr* e) const
        {
            auto* sl = dynamic_cast<ast::StructLiteralExpr*>(e);
            if (!sl)
                return false;
            if (!is_struct_like(expected))
                return false;
            set_expr_type(sl, expected);
            return true;
        }

        bool coerce_bool_literal_to(TypeId expected, ast::Expr* e)
        {
            auto* bl = dynamic_cast<ast::BoolLiteralExpr*>(e);
            if (!bl)
                return false;

            TypeId bool_tid = builtin_tid(p5_, builtin_cache_, BuiltinType::Bool);
            if (!is_valid_typeid(p5_, bool_tid) || !is_valid_typeid(p5_, expected))
                return false;

            if (expected.value != bool_tid.value)
                return false;

            set_expr_type(bl, bool_tid);
            return true;
        }

        std::optional<BuiltinType> builtin_of(TypeId t) const
        {
            if (!is_valid_typeid(p5_, t))
                return std::nullopt;
            const TypeNode& n = p5_.types.nodes[t.value];
            if (n.kind != TypeKind::Builtin)
                return std::nullopt;
            return n.builtin;
        }

        static bool builtin_int_info(BuiltinType b, std::uint32_t& bits, bool& is_signed)
        {
            switch (b)
            {
            case BuiltinType::I8: bits = 8; is_signed = true; return true;
            case BuiltinType::I16: bits = 16; is_signed = true; return true;
            case BuiltinType::I32: bits = 32; is_signed = true; return true;
            case BuiltinType::I64: bits = 64; is_signed = true; return true;
            case BuiltinType::I128: bits = 128; is_signed = true; return true;

            case BuiltinType::U8: bits = 8; is_signed = false; return true;
            case BuiltinType::U16: bits = 16; is_signed = false; return true;
            case BuiltinType::U32: bits = 32; is_signed = false; return true;
            case BuiltinType::U64: bits = 64; is_signed = false; return true;
            case BuiltinType::U128: bits = 128; is_signed = false; return true;

            default:
                return false;
            }
        }

        static U128 lit_magnitude_u128(const IntLitValue& v)
        {
            return std::visit([](auto x) -> U128 { return static_cast<U128>(x); }, v);
        }

        static U128 max_unsigned_bits(std::uint32_t bits)
        {
            if (bits >= 128)
                return ~static_cast<U128>(0);
            return (static_cast<U128>(1) << bits) - static_cast<U128>(1);
        }

        static U128 max_signed_bits(std::uint32_t bits)
        {
            if (bits <= 1)
                return 0;
            if (bits >= 128)
                return (static_cast<U128>(1) << 127) - static_cast<U128>(1);
            return (static_cast<U128>(1) << (bits - 1)) - static_cast<U128>(1);
        }

        bool coerce_int_literal_to(TypeId expected, ast::Expr* e) const
        {
            auto* il = dynamic_cast<ast::IntLiteralExpr*>(e);
            if (!il)
                return false;

            auto it = out_.int_id.find(il);
            if (it == out_.int_id.end())
                return false;

            const auto b = builtin_of(expected);
            if (!b.has_value())
                return false;

            std::uint32_t bits = 0;
            bool is_signed = false;
            if (!builtin_int_info(*b, bits, is_signed))
                return false;

            const IntLitValue& cur = out_.ints[it->second];
            const U128 mag = lit_magnitude_u128(cur);

            const U128 maxv = is_signed ? max_signed_bits(bits) : max_unsigned_bits(bits);
            if (mag > maxv)
            {
                pass7_log_numeric_err(out_.errors,
                                      il->location_,
                                      pass7_module_prefix() + "IntOverflow: integer literal does not fit expected type",
                                      il->v_);
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

        // NEW: coerce array literal to Box<T> (runtime array)
        bool coerce_dyn_array_literal_to(TypeId expected, ast::Expr* e)
        {
            auto* al = dynamic_cast<ast::ArrayLiteralExpr*>(e);
            if (!al)
                return false;

            DynArrayInfo di = as_dyn_array_type(expected);
            if (!di.ok)
                return false;

            set_expr_type(al, expected);

            for (std::uint64_t i = 0; i < static_cast<std::uint64_t>(al->v_.size()); ++i)
            {
                ast::Expr* el = al->v_[static_cast<size_t>(i)];
                if (!el)
                    continue;

                (void)coerce_int_literal_to(di.elem, el);
                (void)coerce_bool_literal_to(di.elem, el);
                (void)coerce_struct_literal_to(di.elem, el);
                (void)coerce_array_literal_to(di.elem, el);       // if T is fixed array
                (void)coerce_dyn_array_literal_to(di.elem, el);   // if T is Box<...>

                TypeId et = get_expr_type(el);

                if (!is_valid_typeid(p5_, et) || !is_valid_typeid(p5_, di.elem))
                {
                    pass7_log_text(out_.errors,
                                   el->location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: cannot type-check dyn array literal element (unknown type)");
                    continue;
                }

                if (!assignable(di.elem, et))
                {
                    std::ostringstream oss;
                    oss << pass7_module_prefix()
                        << "UnknownExprType: type mismatch in dyn array literal element #" << i
                        << " (expected=" << di.elem.value << ", got=" << et.value << ")";
                    pass7_log_text(out_.errors, el->location_, oss.str());
                }
            }

            return true;
        }

        bool coerce_array_literal_to(TypeId expected, ast::Expr* e)
        {
            auto* al = dynamic_cast<ast::ArrayLiteralExpr*>(e);
            if (!al)
                return false;

            ArrayInfo ai = as_array_type(expected);
            if (!ai.ok)
                return false;

            set_expr_type(al, expected);

            const auto got = static_cast<std::uint64_t>(al->v_.size());
            const std::uint64_t want = ai.len;

            if (got != want)
            {
                std::ostringstream oss;
                oss << pass7_module_prefix()
                    << "UnknownExprType: array literal length mismatch (expected " << want
                    << ", got " << got << ")";
                pass7_log_text(out_.errors, al->location_, oss.str());
            }

            const std::uint64_t n = std::min(got, want);

            for (std::uint64_t i = 0; i < n; ++i)
            {
                ast::Expr* el = al->v_[static_cast<size_t>(i)];
                if (!el)
                    continue;

                (void)coerce_int_literal_to(ai.elem, el);
                (void)coerce_bool_literal_to(ai.elem, el);
                (void)coerce_struct_literal_to(ai.elem, el);
                (void)coerce_array_literal_to(ai.elem, el);
                (void)coerce_dyn_array_literal_to(ai.elem, el); // NEW: element could be Box<...>

                TypeId et = get_expr_type(el);

                if (!is_valid_typeid(p5_, et) || !is_valid_typeid(p5_, ai.elem))
                {
                    pass7_log_text(out_.errors,
                                   el->location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: cannot type-check array literal element (unknown type)");
                    continue;
                }

                if (!assignable(ai.elem, et))
                {
                    std::ostringstream oss;
                    oss << pass7_module_prefix()
                        << "UnknownExprType: type mismatch in array literal element #" << i
                        << " (expected=" << ai.elem.value << ", got=" << et.value << ")";
                    pass7_log_text(out_.errors, el->location_, oss.str());
                }
            }

            return true;
        }

        TypeId intern_ref_tid(TypeId inner, bool mut) const
        {
            if (!is_valid_typeid(p5_, inner))
                return TypeId{UINT32_MAX};

            TypeKey k{};
            k.kind = TypeKind::Ref;
            k.inner = inner;
            k.ref_mut = mut;

            return p5_.types.get_or_intern(k);
        }

        TypeId intern_box_tid(TypeId inner) const
        {
            if (!is_valid_typeid(p5_, inner))
                return TypeId{UINT32_MAX};

            TypeKey k{};
            k.kind = TypeKind::Box;
            k.inner = inner;

            return p5_.types.get_or_intern(k);
        }

        TypeId intern_array_fixed_tid(TypeId elem, std::uint64_t len) const
        {
            if (!is_valid_typeid(p5_, elem))
                return TypeId{UINT32_MAX};

            TypeKey k{};
            k.kind = TypeKind::ArrayFixed;
            k.elem = elem;
            k.array_len = len;

            return p5_.types.get_or_intern(k);
        }

        using SubstMap = std::unordered_map<lex::SymId, TypeId>;

        TypeId instantiate_type(TypeId t, const SubstMap& subst) const
        {
            if (!is_valid_typeid(p5_, t))
                return TypeId{UINT32_MAX};

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
                    return is_valid_typeid(p5_, elem2)
                               ? intern_array_fixed_tid(elem2, n.array_len)
                               : TypeId{UINT32_MAX};
                }

            default:
                return t;
            }
        }

        bool instantiate_sig_for_call(FnSig& sig, const ast::CallExpr& c) const
        {
            if (sig.type_params.empty())
            {
                if (!c.typeArgs_.empty())
                {
                    pass7_log_text(out_.errors,
                                   c.location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: type arguments provided but callee is not generic");
                    return false;
                }
                return true;
            }

            const size_t want = sig.type_params.size();
            const size_t got = c.typeArgs_.size();

            if (want != got)
            {
                std::ostringstream oss;
                oss << pass7_module_prefix()
                    << "UnknownExprType: wrong number of type arguments (expected " << want
                    << ", got " << got << ")";
                pass7_log_text(out_.errors, c.location_, oss.str());
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
                    oss << pass7_module_prefix()
                        << "UnknownExprType: cannot resolve type argument #" << i;
                    pass7_log_text(out_.errors, c.location_, oss.str());
                    return false;
                }
                subst.emplace(sig.type_params[i], tid);
            }

            for (auto& p : sig.params)
            {
                p = instantiate_type(p, subst);
                if (!is_valid_typeid(p5_, p))
                {
                    pass7_log_text(out_.errors,
                                   c.location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: failed to instantiate generic parameter type");
                    return false;
                }
            }

            sig.ret = instantiate_type(sig.ret, subst);
            if (!is_valid_typeid(p5_, sig.ret))
            {
                pass7_log_text(out_.errors,
                               c.location_,
                               pass7_module_prefix()
                               + "UnknownExprType: failed to instantiate generic return type");
                return false;
            }

            return true;
        }

        std::optional<TypeId> struct_field_type(TypeId structTy, lex::SymId fieldName) const
        {
            if (!is_valid_typeid(p5_, structTy))
                return std::nullopt;

            const TypeNode& tn = p5_.types.nodes[structTy.value];

            if (tn.kind == TypeKind::Struct)
            {
                auto itLay = p5_.struct_layout.find(tn.struct_id);
                if (itLay == p5_.struct_layout.end())
                    return std::nullopt;

                const StructLayout& lay = itLay->second;

                auto itIdx = lay.name_to_index.find(fieldName);
                if (itIdx == lay.name_to_index.end())
                    return std::nullopt;

                const uint32_t idx = itIdx->second;
                if (idx >= lay.field_types_in_order.size())
                    return std::nullopt;

                TypeId ft = lay.field_types_in_order[idx];
                return is_valid_typeid(p5_, ft) ? std::optional<TypeId>{ft} : std::nullopt;
            }

            return std::nullopt;
        }

        const LocalSlotInfo* local_slot_info_of_ref(const ast::RefExpr& r) const
        {
            if (!fb_)
                return nullptr;
            auto itb = fb_->ref_binding.find(&r);
            if (itb == fb_->ref_binding.end())
                return nullptr;

            const Binding& b = itb->second;
            if (b.kind != BindingKind::LocalSlot)
                return nullptr;

            if (b.slot.index >= fb_->slots.size())
                return nullptr;
            return &fb_->slots[b.slot.index];
        }

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
            if (!e)
                return pr;
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

                // fixed array element place
                if (ArrayInfo ai = as_array_type(bt); ai.ok)
                {
                    pr.is_place = true;
                    pr.is_mutable = base.is_mutable;
                    pr.type = ai.elem;
                    return pr;
                }

                // NEW: Box<T> element place
                if (DynArrayInfo di = as_dyn_array_type(bt); di.ok)
                {
                    pr.is_place = true;
                    pr.is_mutable = base.is_mutable;
                    pr.type = di.elem;
                    return pr;
                }

                pr.is_place = true;
                pr.is_mutable = base.is_mutable;
                pr.type = TypeId{UINT32_MAX};
                return pr;
            }

            if (auto* fe = dynamic_cast<ast::FieldExpr*>(e))
            {
                PlaceResult base = analyze_place(fe->base_);
                if (!base.is_place)
                    return pr;

                TypeId bt = get_expr_type(fe->base_);
                if (RefInfo ri = as_ref_type(bt); ri.ok)
                    bt = ri.pointee;

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

        ast::FnDecl* find_user_fn_decl(FnId id) const
        {
            for (const ModuleGlobals& mg : p4_.modules)
                for (const FnSym& fs : mg.fns)
                    if (fs.id == id)
                        return fs.decl;
            return nullptr;
        }

        ast::LoadFnDecl* find_user_load_fn_decl(LoadFnId id) const
        {
            for (const ModuleGlobals& mg : p4_.modules)
                for (const LoadFnSym& ls : mg.load_fns)
                    if (ls.id == id)
                        return ls.decl;
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

            auto try_reserved_sig_by_name = [&]() -> bool
            {
                if (!p3_5_ || !leafNameOpt.has_value())
                    return false;

                auto it = p3_5_->sigs.fns.find(*leafNameOpt);
                if (it == p3_5_->sigs.fns.end())
                    return false;

                ast::FnDecl* fd = it->second;
                if (!fd)
                    return false;

                sig.type_params.clear();
                sig.type_params.reserve(fd->typeParamsDecls_.size());
                for (auto* tp : fd->typeParamsDecls_)
                    if (tp)
                        sig.type_params.push_back(tp->name_);

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
                if (try_reserved_sig_by_name())
                    return sig;

                ast::FnDecl* fd = find_user_fn_decl(b.fn);
                if (!fd)
                    return sig;

                sig.type_params.clear();
                sig.type_params.reserve(fd->typeParamsDecls_.size());
                for (auto* tp : fd->typeParamsDecls_)
                    if (tp)
                        sig.type_params.push_back(tp->name_);

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
                if (!ld)
                    return sig;

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
                if (try_reserved_sig_by_name())
                    return sig;
                return sig;
            }

            return sig;
        }
    };


    void Pass7TypeCheckVisitor::visit(ast::Module& m)
    {
        (void)m;
        mb_ = unit_i_ < p6_.modules.size() ? &p6_.modules[unit_i_] : nullptr;
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

        cur_fn_ret_ = type_of_typeexpr(f.ret_);
        cur_fn_loc_ = f.location_;

        ast::visitor::OverallVisitor::visit(f);

        cur_fn_ret_ = TypeId{UINT32_MAX};
        cur_fn_loc_ = {};
        fb_ = nullptr;
    }

    void Pass7TypeCheckVisitor::visit(ast::ReturnStatement& r)
    {
        if (r.expr_)
        {
            (void)coerce_int_literal_to(cur_fn_ret_, r.expr_);
            (void)coerce_bool_literal_to(cur_fn_ret_, r.expr_);
            (void)coerce_struct_literal_to(cur_fn_ret_, r.expr_);
            (void)coerce_array_literal_to(cur_fn_ret_, r.expr_);
            (void)coerce_dyn_array_literal_to(cur_fn_ret_, r.expr_); // NEW

            TypeId got = get_expr_type(r.expr_);
            TypeId want = cur_fn_ret_;

            if (!is_valid_typeid(p5_, want) || !is_valid_typeid(p5_, got))
            {
                pass7_log_text(out_.errors,
                               r.location_,
                               pass7_module_prefix()
                               + "UnknownExprType: cannot type-check return expression (unknown type)");
                return;
            }

            TypeId void_tid = builtin_tid(p5_, builtin_cache_, BuiltinType::Void);
            if (is_valid_typeid(p5_, void_tid) && want.value == void_tid.value)
            {
                pass7_log_text(out_.errors,
                               r.location_,
                               pass7_module_prefix()
                               + "TypeMismatchInit: returning a value from a Void function");
                return;
            }

            if (!assignable(want, got))
            {
                std::ostringstream oss;
                oss << pass7_module_prefix()
                    << "TypeMismatchInit: return type mismatch (expected " << want.value
                    << ", got " << got.value << ")";
                pass7_log_text(out_.errors, r.location_, oss.str());
            }

            return;
        }

        TypeId void_tid = builtin_tid(p5_, builtin_cache_, BuiltinType::Void);
        if (is_valid_typeid(p5_, void_tid) && is_valid_typeid(p5_, cur_fn_ret_) &&
            cur_fn_ret_.value != void_tid.value)
        {
            std::ostringstream oss;
            oss << pass7_module_prefix()
                << "UnknownExprType: missing return value (function ret type "
                << cur_fn_ret_.value << ")";
            pass7_log_text(out_.errors, r.location_, oss.str());
        }
    }

    void Pass7TypeCheckVisitor::visit(ast::BoolLiteralExpr& b)
    {
        TypeId t = builtin_tid(p5_, builtin_cache_, BuiltinType::Bool);
        set_expr_type(&b, t);
    }

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
        if (std::holds_alternative<F32>(v))
            t = builtin_tid(p5_, builtin_cache_, BuiltinType::F32);
        else
            t = builtin_tid(p5_, builtin_cache_, BuiltinType::F64);

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
            if (si.var_decl)
                texpr = si.var_decl->type_;
            if (si.param_decl)
                texpr = si.param_decl->type_;

            set_expr_type(&r, type_of_typeexpr(texpr));
            return;
        }

        set_expr_type(&r, TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::UnaryExpr& u)
    {
        if (u.expr_)
            u.expr_->accept(*this);

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
                    pass7_log_text(out_.errors,
                                   u.location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: cannot take address-of non-place expression");
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
                    pass7_log_text(out_.errors,
                                   u.location_,
                                   pass7_module_prefix()
                                   + "UnknownExprType: cannot take &mut of non-place expression");
                    outT = TypeId{UINT32_MAX};
                    break;
                }
                if (!pr.is_mutable)
                {
                    pass7_log_text(out_.errors,
                                   u.location_,
                                   pass7_module_prefix()
                                   + "ImmutableAssign: cannot take &mut of immutable place");
                    outT = TypeId{UINT32_MAX};
                    break;
                }
                outT = intern_ref_tid(pr.type, /*mut=*/true);
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
            pass7_log_text(out_.errors,
                           u.location_,
                           pass7_module_prefix()
                           + "UnknownExprType: cannot form reference type (missing &T / &mut T in Pass5)");
        }

        set_expr_type(&u, outT);
    }

    void Pass7TypeCheckVisitor::visit(ast::BinaryExpr& b)
    {
        if (b.lhs_)
            b.lhs_->accept(*this);
        if (b.rhs_)
            b.rhs_->accept(*this);

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
        if (i.base_)
            i.base_->accept(*this);
        if (i.index_)
            i.index_->accept(*this);

        TypeId bt = get_expr_type(i.base_);

        if (ArrayInfo ai = as_array_type(bt); ai.ok)
        {
            set_expr_type(&i, ai.elem);
            return;
        }

        // NEW: Box<T> indexing returns T
        if (DynArrayInfo di = as_dyn_array_type(bt); di.ok)
        {
            set_expr_type(&i, di.elem);
            return;
        }

        set_expr_type(&i, TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::FieldExpr& f)
    {
        if (f.base_)
            f.base_->accept(*this);

        TypeId bt = get_expr_type(f.base_);

        // AUTO-DEREF: if base is &S or &mut S, look fields up on S
        if (RefInfo ri = as_ref_type(bt); ri.ok)
            bt = ri.pointee;

        if (auto ft = struct_field_type(bt, f.field); ft.has_value())
            set_expr_type(&f, *ft);
        else
            set_expr_type(&f, TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::VarStmt& v)
    {
        if (!v.type_ || !v.init_)
            return;

        const TypeId dst = type_of_typeexpr(v.type_);

        (void)coerce_dyn_array_literal_to(dst, v.init_); // NEW
        (void)coerce_array_literal_to(dst, v.init_);
        (void)coerce_bool_literal_to(dst, v.init_);
        (void)coerce_int_literal_to(dst, v.init_);
        (void)coerce_struct_literal_to(dst, v.init_);

        const TypeId src = get_expr_type(v.init_);

        if (!is_valid_typeid(p5_, dst) || !is_valid_typeid(p5_, src))
        {
            pass7_log_text(out_.errors,
                           v.location_,
                           pass7_module_prefix()
                           + "UnknownExprType: cannot type-check initializer (unknown type)");
            return;
        }

        if (!assignable(dst, src))
        {
            std::ostringstream oss;
            oss << pass7_module_prefix()
                << "TypeMismatchInit: type mismatch in initializer (dst=" << dst.value
                << ", src=" << src.value << ")";

            pass7_log_text(out_.errors, v.location_, oss.str());
        }
    }

    void Pass7TypeCheckVisitor::visit(ast::AssignExpr& a)
    {
        if (a.lhs_)
            a.lhs_->accept(*this);
        if (a.rhs_)
            a.rhs_->accept(*this);

        PlaceResult pr = analyze_place(a.lhs_);
        if (!pr.is_place)
        {
            pass7_log_text(out_.errors,
                           a.location_,
                           pass7_module_prefix()
                           + "NonAssignableLhs: left-hand side of assignment is not assignable");
        }
        else if (!pr.is_mutable)
        {
            pass7_log_begin(out_.errors, a.location_);
            log_msg(out_.errors, pass7_module_prefix() + "ImmutableAssign: cannot assign to immutable place");
            if (auto* r = dynamic_cast<ast::RefExpr*>(a.lhs_))
                log_ident(out_.errors, r->name, r->location_);
        }

        const TypeId dst = get_expr_type(a.lhs_);

        (void)coerce_dyn_array_literal_to(dst, a.rhs_); // NEW
        (void)coerce_int_literal_to(dst, a.rhs_);
        (void)coerce_bool_literal_to(dst, a.rhs_);
        (void)coerce_struct_literal_to(dst, a.rhs_);
        (void)coerce_array_literal_to(dst, a.rhs_);

        const TypeId src = get_expr_type(a.rhs_);

        if (!is_valid_typeid(p5_, dst) || !is_valid_typeid(p5_, src))
        {
            pass7_log_text(out_.errors,
                           a.location_,
                           pass7_module_prefix()
                           + "UnknownExprType: cannot type-check assignment (unknown type)");
            return;
        }

        if (!assignable(dst, src))
        {
            std::ostringstream oss;
            oss << pass7_module_prefix()
                << "TypeMismatchAssign: type mismatch in assignment (dst=" << dst.value
                << ", src=" << src.value << ")";
            pass7_log_text(out_.errors, a.location_, oss.str());
        }

        set_expr_type(&a, dst);
    }

    void Pass7TypeCheckVisitor::visit(ast::ArrayLiteralExpr& a)
    {
        for (auto& ep : a.v_)
            if (ep)
                ep->accept(*this);

        auto it = out_.expr_type.find(&a);
        if (it != out_.expr_type.end() && is_valid_typeid(p5_, it->second))
            return;

        pass7_log_text(out_.errors,
                       a.location_,
                       pass7_module_prefix()
                       + "UnknownExprType: cannot infer array literal element type (no context)");
        set_expr_type(&a, TypeId{UINT32_MAX});
    }

    void Pass7TypeCheckVisitor::visit(ast::CharLiteralExpr& c)
    {
        auto it = out_.char_id.find(&c);
        if (it == out_.char_id.end())
        {
            set_expr_type(&c, TypeId{UINT32_MAX});
            return;
        }

        TypeId t = builtin_tid(p5_, builtin_cache_, BuiltinType::Char);
        set_expr_type(&c, t);
    }

    void Pass7TypeCheckVisitor::visit(ast::CallExpr& c)
    {
        if (c.callee_)
            c.callee_->accept(*this);

        FnSig sig = signature_of_callee(c.callee_);
        if (!sig.ok)
        {
            pass7_log_begin(out_.errors, c.location_);
            log_msg(out_.errors, pass7_module_prefix()
                    + "NonCallableCallee: callee is not callable (expected fn or load fn)");
            if (auto nm = callee_leaf_name(c.callee_); nm.has_value())
                log_ident(out_.errors, *nm, c.location_);
            set_expr_type(&c, TypeId{UINT32_MAX});
            return;
        }

        if (!instantiate_sig_for_call(sig, c))
        {
            set_expr_type(&c, TypeId{UINT32_MAX});
            return;
        }

        if (c.args_.size() != sig.params.size())
        {
            std::ostringstream oss;
            oss << pass7_module_prefix()
                << "WrongArgCount: wrong number of arguments (expected "
                << sig.params.size() << ", got " << c.args_.size() << ")";
            pass7_log_text(out_.errors, c.location_, oss.str());
            set_expr_type(&c, sig.ret);
            return;
        }

        for (size_t i = 0; i < c.args_.size(); ++i)
        {
            TypeId pt = sig.params[i];

            (void)coerce_dyn_array_literal_to(pt, c.args_[i]); // NEW
            (void)coerce_int_literal_to(pt, c.args_[i]);
            (void)coerce_bool_literal_to(pt, c.args_[i]);
            (void)coerce_struct_literal_to(pt, c.args_[i]);
            (void)coerce_array_literal_to(pt, c.args_[i]);

            TypeId at = get_expr_type(c.args_[i]);

            if (!is_valid_typeid(p5_, at) || !is_valid_typeid(p5_, pt))
            {
                pass7_log_text(out_.errors,
                               c.location_,
                               pass7_module_prefix()
                               + "UnknownExprType: cannot type-check call (unknown arg/param type)");
                continue;
            }

            if (!assignable(pt, at))
            {
                std::ostringstream oss;
                oss << pass7_module_prefix()
                    << "TypeMismatchCallArg: type mismatch in call arg #" << i
                    << " (param=" << pt.value << ", arg=" << at.value << ")";
                const lex::Loc loc = c.args_[i] ? c.args_[i]->location_ : c.location_;
                pass7_log_text(out_.errors, loc, oss.str());
            }
        }

        set_expr_type(&c, sig.ret);
    }


    static ModuleId pass7_unit_module_id(const Pass4Result& p4,
                                         const Pass6Result& p6,
                                         std::uint32_t unit_i)
    {
        if (unit_i < p4.modules.size())
            return p4.modules[unit_i].module_id;

        if (unit_i < p6.modules.size())
            return p6.modules[unit_i].module_id;

        return kInvalidModuleId;
    }

    Pass7Result run_pass7(const Translation& tr,
                          const CompilerContext& ctx,
                          const Pass4Result& p4,
                          Pass5Result& p5,
                          const Pass6Result& p6,
                          const Pass3_5Result* p3_5)
    {
        Pass7Result out{};

        for (std::uint32_t unit_i = 0;
             unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m)
                continue;

            const std::vector<lex::SymId>* mod_path = &kPass7EmptyPath;
            if (m->pathExpr_)
                mod_path = &m->pathExpr_->path_;

            Pass7UnitModuleScope scope(pass7_unit_module_id(p4, p6, unit_i), mod_path);

            Pass7LiteralLoweringVisitor vis(ctx, out);
            m->accept(vis);
        }

        for (std::uint32_t unit_i = 0;
             unit_i < static_cast<std::uint32_t>(tr.units.size()); ++unit_i)
        {
            ast::Module* m = tr.units[unit_i].module_;
            if (!m)
                continue;

            const std::vector<lex::SymId>* mod_path = &kPass7EmptyPath;
            if (m->pathExpr_)
                mod_path = &m->pathExpr_->path_;

            Pass7UnitModuleScope scope(pass7_unit_module_id(p4, p6, unit_i), mod_path);

            Pass7TypeCheckVisitor tcv(p4, p5, p6, p3_5, out, unit_i);
            m->accept(tcv);
        }

        return out;
    }
}
