#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "reserved_struct.hpp"
#include "visit/overallvisitor.hpp"
#include "translation.hpp"
#include "type_system.hpp"

#include "module/module.hpp"
#include "decl/fn_decl.hpp"

// You must have this enum somewhere. If not, create it.
// enum class RuntimeIntrinsic : uint8_t { box_new, box_free, box_len, box_get, box_set, print };
#include "runtime_intrinsics.hpp"

namespace sema
{
    struct ReservedNames final
    {
        std::unordered_set<lex::SymId> value;
        std::unordered_set<lex::SymId> type;

        bool is_reserved_value(lex::SymId s) const { return value.contains(s); }
        bool is_reserved_type(lex::SymId s) const { return type.contains(s); }
    };

    struct IntrinsicSigs final
    {
        // Prototype pointers (so later passes can read param lists etc. if needed)
        std::unordered_map<lex::SymId, ast::FnDecl*> fns;
        std::unordered_map<lex::SymId, ReservedStruct> structs;
    };

    // The SymIds of the well-known intrinsic names (must come from your interner)
    struct IntrinsicNameIds final
    {
        // types
        lex::SymId sym_Box{};
        lex::SymId sym_Str{};

        // values
        lex::SymId sym_box_new{};
        lex::SymId sym_box_free{};
        lex::SymId sym_box_len{};
        lex::SymId sym_box_get{};
        lex::SymId sym_box_set{};
        lex::SymId sym_print{};
    };

    struct Pass3_5Diagnostic final
    {
        enum class Code : uint8_t
        {
            DuplicateReservedValueName,
            DuplicateReservedTypeName,
        };

        Code code{};
        lex::Loc loc{};
        std::string message;
    };

    struct Pass3_5Result final
    {
        // Quick name checks
        ReservedNames reserved;

        // Prototype pointers and reserved-struct flags
        IntrinsicSigs sigs;

        // Stable “reserved global ids”
        std::unordered_map<lex::SymId, StructId> struct_by_name;
        std::unordered_map<lex::SymId, FnId> fn_by_name;
        std::unordered_map<lex::SymId, LoadFnId> load_fn_by_name;

        // NEW: name classification used by Pass4.5/Pass6/Pass9.5
        std::unordered_map<lex::SymId, RuntimeIntrinsic> intrinsic_by_name;

        std::vector<Pass3_5Diagnostic> diagnostics;

        bool ok() const { return diagnostics.empty(); }
    };

    class Pass3_5ReservedIndexVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        explicit Pass3_5ReservedIndexVisitor(Pass3_5Result& out, IntrinsicNameIds ids)
            : out_(out), ids_(ids)
        {
        }

        void visit(ast::FnDecl& f) override;
        void visit(ast::StructDecl& s) override;
        void visit(ast::Module& m) override;

    private:
        Pass3_5Result& out_;
        IntrinsicNameIds ids_{};

        std::uint32_t next_fn_index_ = 0;
        std::uint32_t next_struct_index_ = 0;
        std::uint32_t next_load_fn_index_ = 0;

        void diag(Pass3_5Diagnostic::Code code, const lex::Loc& loc, std::string msg) const;
    };

    // Build the reserved index from your reserved/builtins Translation
    Pass3_5Result run_pass3_5_reserved_index(const Translation& reserved_tr, IntrinsicNameIds ids);
} // namespace sema
