//
// Created by yhwach on 12/26/25.
//

#ifndef INZ_MODULE_BUIDLER_PASS_HPP
#define INZ_MODULE_BUIDLER_PASS_HPP
#include "module_import_pass.hpp"

namespace sema
{
    static uint64_t hashPath(llvm::ArrayRef<lex::SymId> segs)
    {
        uint64_t h = 1469598103934665603ull; // FNV-1a base
        for (lex::SymId s : segs)
        {
            uint64_t x = s; // adapt if SymId is struct
            h ^= x;
            h *= 1099511628211ull;
        }

        return h;
    }

    struct ModulePassBuilder
    {
        hir::pass::ModulePassDB db;

        hir::pass::ModuleId addModule(hir::pass::FileId file,
                                      llvm::ArrayRef<lex::SymId> package_segs,
                                      uint32_t unit_index,
                                      uint32_t arena_index)
        {
            hir::pass::ModuleId id = static_cast<hir::pass::ModuleId>(db.modules.size());

            const PathRef pref = db.pool.append(package_segs);
            const uint64_t h = hashPath(db.pool.view(pref));
            const lex::SymId leaf = package_segs.empty() ? lex::SymId{} : package_segs.back();

            hir::pass::ModuleRec m{};
            m.file = file;
            m.package_path = pref;
            m.leaf_name = leaf;
            m.import_begin = static_cast<uint32_t>(db.imports.size());
            m.import_count = 0;
            m.edge_begin = static_cast<uint32_t>(db.graph.edges.size());
            m.edge_count = 0;
            m.unit_index = unit_index;
            m.arena_index = arena_index;

            db.modules.push_back(m);
            db.module_by_file.try_emplace(file, id);

            // IMPORTANT: key uses the pooled ref and precomputed hash
            db.module_by_pathkey.try_emplace(hir::pass::PathKey{h, pref}, id);

            return id;
        }

        hir::ImportId addImport(hir::pass::ModuleId owner,
                                llvm::ArrayRef<lex::SymId> import_segs,
                                lex::SymId alias,
                                uint16_t flags,
                                hir::pass::Span span)
        {
            hir::ImportId iid = static_cast<hir::ImportId>(db.imports.size());
            PathRef pref = db.pool.append(import_segs);

            hir::pass::ImportRec r{};
            r.owner = owner;
            r.target = hir::pass::kInvalidModule;
            r.path = pref;
            r.alias = alias;
            r.flags = flags;
            r.span = span;

            db.imports.push_back(r);
            db.modules[owner].import_count++;

            return iid;
        }

        // Resolve edge if the imported path matches a known module path
        void tryAddEdgeFromImport(hir::ImportId iid) const
        {
            auto& imp = db.imports[iid];
            const auto segs = db.pool.view(imp.path);
            const uint64_t h = hashPath(segs);

            // To lookup, we need a PathKey with matching (hash,ref).
            // But our PathKeyInfo equality compares ref too; so we do not use it directly for “content lookup”.
            // Instead: use a second map keyed by hash -> list, OR use a different DenseMap key strategy.
            //
            // Simplest optimized solution: maintain an additional map hash->ModuleId, and on collision verify content.
        }
    };
}

#endif //INZ_MODULE_BUIDLER_PASS_HPP
