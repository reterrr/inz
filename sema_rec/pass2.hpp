// sema/pass2.hpp
#pragma once

#include <cstdint>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "ast/nodes/visit/overallvisitor.hpp"
#include "module/module.hpp"
#include "translation.hpp"
#include "type_system.hpp"

namespace sema
{
    // Use a consistent invalid marker (avoids silently mapping to module 0).
    inline constexpr ModuleId kInvalidModuleId{ std::numeric_limits<std::uint32_t>::max() };

    struct ModuleEntry final
    {
        ModuleId id{};
        std::uint32_t unit_index = 0; // which translation unit / file
        std::string key;             // stable module key derived from pathExpr_
        lex::Loc loc{};
    };

    struct Pass2Diagnostic final
    {
        enum class Code : std::uint8_t
        {
            DuplicateModuleName,
        };

        Code code{};
        ModuleId module = kInvalidModuleId; // module involved in the diagnostic (usually first-seen module)
        lex::Loc loc{};
        std::string message;
    };

    struct Pass2Result final
    {
        std::vector<ModuleEntry> modules;                 // indexed by ModuleId.value
        std::unordered_map<std::string, ModuleId> by_key; // module key -> id

        std::vector<ModuleId> unit_to_module;             // [unit_index] -> ModuleId
        std::vector<std::uint32_t> module_to_unit;        // [ModuleId.value] -> unit_index

        std::vector<Pass2Diagnostic> diagnostics;
        bool ok() const { return diagnostics.empty(); }
    };

    class Pass2ModuleIndexVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass2ModuleIndexVisitor(Pass2Result& out, std::uint32_t unit_index)
            : out_(out), unit_index_(unit_index)
        {}

        void visit(ast::Module& m) override;

    private:
        Pass2Result& out_;
        std::uint32_t unit_index_ = 0;

        static std::string make_module_key(const ast::Module& m);
        static std::string join_sym_path(const std::vector<lex::SymId>& segs);
    };

    Pass2Result run_pass2_module_index(const Translation& tr);

} // namespace sema
