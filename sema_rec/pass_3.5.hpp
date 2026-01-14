#pragma once

#include "logging_entities.hpp"
#include "reserved_struct.hpp"
#include "runtime_intrinsics.hpp"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "visit/overallvisitor.hpp"
#include "translation.hpp"
#include "type_system.hpp"

#include "module/module.hpp"
#include "decl/fn_decl.hpp"

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
        std::unordered_map<lex::SymId, ast::FnDecl*> fns;
        std::unordered_map<lex::SymId, ReservedStruct> structs;
    };


    struct IntrinsicNameIds final
    {
        lex::SymId sym_Box{};
        lex::SymId sym_Str{};


        lex::SymId sym_box_new{};
        lex::SymId sym_box_free{};
        lex::SymId sym_box_len{};
        lex::SymId sym_box_get{};
        lex::SymId sym_box_set{};
        lex::SymId sym_print{};
        lex::SymId sym_put{};
        lex::SymId sym_nl{};
    };

    struct Pass3_5Result final
    {
        ReservedNames reserved;


        IntrinsicSigs sigs;


        std::unordered_map<lex::SymId, StructId> struct_by_name;
        std::unordered_map<lex::SymId, FnId> fn_by_name;
        std::unordered_map<lex::SymId, LoadFnId> load_fn_by_name;


        std::unordered_map<lex::SymId, RuntimeIntrinsic> intrinsic_by_name;


        LogSequence logs;

        bool ok() const { return logs.empty(); }
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
    };


    Pass3_5Result run_pass3_5_reserved_index(const Translation& reserved_tr, IntrinsicNameIds ids);
}
