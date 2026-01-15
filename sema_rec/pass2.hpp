#pragma once

#include "logging_entities.hpp"

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
    inline constexpr ModuleId kInvalidModuleId{
        std::numeric_limits<std::uint32_t>::max()
    };

    struct ModuleEntry final
    {
        ModuleId id{};
        std::uint32_t unit_index = 0;
        std::string key;
        lex::Loc loc{};
    };

    struct Pass2Result final
    {
        std::vector<ModuleEntry> modules;
        std::unordered_map<std::string, ModuleId> by_key;

        std::vector<ModuleId> unit_to_module;
        std::vector<std::uint32_t> module_to_unit;


        LogSequence errors;

        bool ok() const { return errors.empty(); }
    };

    class Pass2ModuleIndexVisitor final : public ast::visitor::OverallVisitor
    {
    public:
        Pass2ModuleIndexVisitor(Pass2Result& out, std::uint32_t unit_index)
            : out_(out), unit_index_(unit_index)
        {
        }

        void visit(ast::Module& m) override;

    private:
        Pass2Result& out_;
        std::uint32_t unit_index_ = 0;


        static std::string join_sym_path_numeric(const std::vector<lex::SymId>& segs);
        static std::string make_module_key_from_path(const std::vector<lex::SymId>& segs);
    };

    Pass2Result run_pass2_module_index(const Translation& tr);
}
