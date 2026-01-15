//
// Created by yhwach on 12/29/25.
//

#ifndef INZ_DUMP_MODULE_TREE_HPP
#define INZ_DUMP_MODULE_TREE_HPP
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>

#include "sema/module_import_pass.hpp" // for ModulePassDB / ModuleTree
#include "compiler_context.hpp"        // ADAPT include to wherever you keep symbol table

namespace sema
{
    // ---- ADAPT THIS: SymId -> string ----
    // Replace body with your actual interner lookup.
    static inline std::string symToString(const CompilerContext& cc, lex::SymId s)
    {
        // Examples you might have:
        // return std::string(cc.syms.view(s));
        // return cc.symTable.toString(s);
        // return cc.intern.view(s).str();
        return static_cast<std::string>(cc.identInterner.view(s));
    }

    struct TreeDumpCfg
    {
        bool showModuleIds = true; // show "<module X>" at leaves
        bool sortKeys = true; // stable output
        uint32_t indent = 0; // spaces
        uint32_t indentStep = 2;
    };

    // Forward decl
    static void dumpTreeNode(std::ostream& os,
                             const ModulePassDB& pass1,
                             const CompilerContext& cc,
                             uint32_t nodeIdx,
                             TreeDumpCfg& cfg);

    static void dumpChildrenAsMap(std::ostream& os,
                                  const ModulePassDB& pass1,
                                  const CompilerContext& cc,
                                  uint32_t nodeIdx,
                                  TreeDumpCfg& cfg)
    {
        const auto& node = pass1.tree.nodes[nodeIdx];

        // Collect keys for sorting
        std::vector<std::pair<lex::SymId, uint32_t>> kv;
        kv.reserve(node.child.size());
        for (const auto& it : node.child)
            kv.emplace_back(it.first, it.second);

        if (cfg.sortKeys)
        {
            std::sort(kv.begin(), kv.end(),
                      [](const auto& a, const auto& b) { return (uint64_t)a.first < (uint64_t)b.first; });
        }

        os << "{";

        bool first = true;
        cfg.indent += cfg.indentStep;

        for (const auto& [seg, childIdx] : kv)
        {
            if (first)
            {
                os << "\n";
                first = false;
            }
            else
            {
                os << ",\n";
            }

            os << std::string(cfg.indent, ' ')
                << "\"" << symToString(cc, seg) << "\" -> ";

            dumpTreeNode(os, pass1, cc, childIdx, cfg);
        }

        cfg.indent -= cfg.indentStep;

        if (!first)
            os << "\n" << std::string(cfg.indent, ' ');

        os << "}";
    }

    static void dumpTreeNode(std::ostream& os,
                             const ModulePassDB& pass1,
                             const CompilerContext& cc,
                             uint32_t nodeIdx,
                             TreeDumpCfg& cfg)
    {
        const auto& node = pass1.tree.nodes[nodeIdx];

        // If leaf node with module AND no children, print "<module X>" or "{}"
        const bool hasChildren = !node.child.empty();
        const bool hasModule = node.module.has_value();

        if (!hasChildren)
        {
            if (hasModule && cfg.showModuleIds)
            {
                os << "<module " << *node.module << ">";
            }
            else if (hasModule && !cfg.showModuleIds)
            {
                os << "{}";
            }
            else
            {
                os << "{}";
            }
            return;
        }

        // Otherwise print nested object
        dumpChildrenAsMap(os, pass1, cc, nodeIdx, cfg);

        // Optional: if this node is ALSO a module endpoint, annotate it
        // (rare, but possible if you allow module path to be prefix of another module path)
        if (hasModule && cfg.showModuleIds)
        {
            os << " /* module " << *node.module << " */";
        }
    }

    // Public API
    static inline void dumpModuleTree(std::ostream& os,
                                      const ModulePassDB& pass1,
                                      const CompilerContext& cc,
                                      TreeDumpCfg cfg = {})
    {
        // Root is node 0
        dumpChildrenAsMap(os, pass1, cc, 0, cfg);
        os << "\n";
    }
}

#endif //INZ_DUMP_MODULE_TREE_HPP
