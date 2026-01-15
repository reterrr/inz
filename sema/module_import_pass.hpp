#ifndef INZ_MODULE_IMPORT_PASS_HPP
#define INZ_MODULE_IMPORT_PASS_HPP

#include <cstdint>
#include <vector>
#include <optional>

#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>

#include "sema/path_pool.hpp"
#include "hir/arena_holder.hpp"
#include "hir/arena.hpp" // getPathSegsFromExprPath

namespace sema
{
    using ModuleId = uint32_t;
    using ImportId = uint32_t;
    using FileId = uint32_t;

    static constexpr ModuleId kInvalidModule = static_cast<ModuleId>(-1);

    // -------------------------------------------
    // Module tree (trie) for hierarchical iteration & exact lookup
    // -------------------------------------------
    struct ModuleTreeNode
    {
        llvm::DenseMap<lex::SymId, uint32_t> child{}; // seg -> node index
        std::optional<ModuleId> module; // full module ends here (canonical)
    };

    struct ModuleTree
    {
        std::vector<ModuleTreeNode> nodes{1}; // nodes[0] = root

        // Insert full path. Returns false if duplicate full module path.
        bool insert(llvm::ArrayRef<lex::SymId> segs, ModuleId mid)
        {
            uint32_t n = 0; // root
            for (lex::SymId s : segs)
            {
                auto it = nodes[n].child.find(s);
                if (it == nodes[n].child.end())
                {
                    const auto nn = static_cast<uint32_t>(nodes.size());
                    nodes.push_back(ModuleTreeNode{});
                    nodes[n].child.try_emplace(s, nn);
                    n = nn;
                }
                else
                {
                    n = it->second;
                }
            }

            if (nodes[n].module.has_value())
                return false;

            nodes[n].module = mid;
            return true;
        }

        std::optional<ModuleId> find(llvm::ArrayRef<lex::SymId> segs) const
        {
            uint32_t n = 0;
            for (lex::SymId s : segs)
            {
                auto it = nodes[n].child.find(s);
                if (it == nodes[n].child.end())
                    return std::nullopt;
                n = it->second;
            }
            return nodes[n].module;
        }
    };

    // -------------------------------------------
    // Records
    // -------------------------------------------
    struct ImportRec
    {
        ModuleId owner{};
        ModuleId target{kInvalidModule}; // resolved module target if known
        PathRef path{}; // pooled segments
        std::optional<lex::SymId> alias{}; // explicit "as"
        lex::SymId bound_name{}; // alias if present, else leaf segment of path
        lex::Loc loc{};
    };

    struct ModuleRec
    {
        FileId file{};
        PathRef package_path{}; // full module name
        lex::SymId leaf_name{}; // last segment (optional, for convenience)
        lex::Loc loc{}; // module loc (good diagnostics)

        uint32_t import_begin{};
        uint32_t import_count{};

        uint32_t edge_begin{};
        uint32_t edge_count{};

        uint32_t unit_index{};
        uint32_t arena_index{};

        uint8_t valid{1}; // 0 if duplicate/invalid; do not resolve to it
        uint8_t _pad[3]{};
    };

    struct ModuleGraphAdj
    {
        std::vector<ModuleId> edges; // concatenated adjacency
        std::vector<ImportId> edge_import; // which import created this edge
    };

    // -------------------------------------------
    // Diagnostics for pass1 (minimal but useful)
    // -------------------------------------------
    enum class ModulePassErrKind : uint8_t
    {
        DuplicateModulePath,
        DuplicateFile,
        DuplicateImportBinding,
        UnknownImportTarget,
        SelfImport
    };

    struct ModulePassError
    {
        ModulePassErrKind kind{};
        FileId file{};
        ModuleId owner{kInvalidModule}; // owning module (if relevant)
        ModuleId existing{kInvalidModule}; // existing module (for duplicates)
        ModuleId duplicate{kInvalidModule}; // duplicate module (for duplicates)
        ImportId import_id{static_cast<ImportId>(-1)}; // for import-related diagnostics
        lex::Loc loc{};
    };

    struct ModulePassDB
    {
        PathPool pool;

        std::vector<ModuleRec> modules;
        std::vector<ImportRec> imports;

        ModuleGraphAdj graph;

        llvm::DenseMap<FileId, ModuleId> module_by_file;

        // Optional: content-based index (kept; good for debugging / alternative lookup).
        // IMPORTANT: only index VALID modules to keep resolution deterministic.
        llvm::DenseMap<uint64_t, llvm::SmallVector<ModuleId, 2>> modules_by_hash;

        // Canonical hierarchical index
        ModuleTree tree;

        std::vector<ModulePassError> errors;
    };

    // -------------------------------------------
    // DB views / iteration helpers (range-based)
    // -------------------------------------------
    namespace sema
    {
        // A simple range over contiguous indices [begin, begin+count)
        template <typename IdT>
        struct IdRange
        {
            uint32_t begin_{};
            uint32_t count_{};

            struct It
            {
                uint32_t i{};
                IdT operator*() const { return static_cast<IdT>(i); }

                It& operator++()
                {
                    ++i;
                    return *this;
                }

                bool operator!=(const It& o) const { return i != o.i; }
            };

            It begin_it() const { return It{begin_}; }
            It end_it() const { return It{begin_ + count_}; }

            It begin() const { return begin_it(); }
            It end() const { return end_it(); }

            bool empty() const { return count_ == 0; }
        };

        // A paired range: edges and their corresponding import ids (same length)
        struct EdgeRange
        {
            const ModuleId* to_begin{};
            const ImportId* via_begin{};
            uint32_t count{};

            struct Item
            {
                ModuleId to{};
                ImportId via{};
            };

            struct It
            {
                const ModuleId* to{};
                const ImportId* via{};
                uint32_t left{};

                Item operator*() const { return Item{*to, *via}; }

                It& operator++()
                {
                    ++to;
                    ++via;
                    --left;
                    return *this;
                }

                bool operator!=(const It& o) const { return left != o.left; }
            };

            It begin() const { return It{to_begin, via_begin, count}; }
            It end() const { return It{to_begin + count, via_begin + count, 0}; }

            bool empty() const { return count == 0; }
        };

        // -------------------------------------------
        // ModulePassDB query helpers
        // -------------------------------------------
        struct ModulePassDBView
        {
            const ModulePassDB& db;

            // --- record access ---
            const ModuleRec& module(ModuleId m) const { return db.modules[(size_t)m]; }
            const ImportRec& import(ImportId i) const { return db.imports[(size_t)i]; }

            // --- pooled path views ---
            llvm::ArrayRef<lex::SymId> modulePath(ModuleId m) const
            {
                return db.pool.view(module(m).package_path);
            }

            llvm::ArrayRef<lex::SymId> importPath(ImportId i) const
            {
                return db.pool.view(import(i).path);
            }

            // --- contiguous ranges ---
            IdRange<ImportId> importsOf(ModuleId m) const
            {
                const auto& mr = module(m);
                return IdRange<ImportId>{mr.import_begin, mr.import_count};
            }

            EdgeRange edgesOf(ModuleId m) const
            {
                const auto& mr = module(m);
                return EdgeRange{
                    db.graph.edges.data() + mr.edge_begin,
                    db.graph.edge_import.data() + mr.edge_begin,
                    mr.edge_count
                };
            }

            // --- graph / resolution helpers ---
            bool isValid(ModuleId m) const { return module(m).valid != 0; }

            // Canonical resolution (trie)
            ModuleId resolveModuleByPath(llvm::ArrayRef<lex::SymId> segs) const
            {
                auto hit = db.tree.find(segs);
                return hit.has_value() ? *hit : kInvalidModule;
            }

            // Convenience: get target module for import (already resolved in pass1)
            ModuleId importTarget(ImportId i) const { return import(i).target; }

            // Convenience: compute bound name from ImportRec (pass1 sets this)
            lex::SymId importBoundName(ImportId i) const { return import(i).bound_name; }
        };
    } // namespace sema


    // -------------------------------------------
    // Hash helpers (SymId must be integral-like)
    // -------------------------------------------
    static uint64_t hashPath(llvm::ArrayRef<lex::SymId> segs)
    {
        uint64_t h = 1469598103934665603ull; // FNV-1a
        for (auto s : segs)
        {
            const uint64_t x = s; // requires SymId convertible to u64
            h ^= x;
            h *= 1099511628211ull;
        }
        return h;
    }

    static bool equalPath(llvm::ArrayRef<lex::SymId> a,
                          llvm::ArrayRef<lex::SymId> b)
    {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i] != b[i]) return false;
        return true;
    }

    static inline lex::SymId leafOf(llvm::ArrayRef<lex::SymId> segs)
    {
        return segs.empty() ? lex::SymId{} : segs.back();
    }

    // -------------------------------------------
    // Builder
    // -------------------------------------------
    struct ModulePassBuilder
    {
        ModulePassDB db;

        ModuleId addModule(FileId file,
                           llvm::ArrayRef<lex::SymId> package_segs,
                           uint32_t unit_index,
                           uint32_t arena_index,
                           const lex::Loc& loc)
        {
            const auto id = static_cast<ModuleId>(db.modules.size());

            // File uniqueness (defensive)
            if (db.module_by_file.find(file) != db.module_by_file.end())
            {
                db.errors.push_back(ModulePassError{
                    .kind = ModulePassErrKind::DuplicateFile,
                    .file = file,
                    .owner = kInvalidModule,
                    .existing = db.module_by_file.lookup(file),
                    .duplicate = id,
                    .import_id = static_cast<ImportId>(-1),
                    .loc = loc
                });
                // Still create an invalid record to keep indices aligned
            }

            // Duplicate module path: do NOT insert duplicates into the trie,
            // and do NOT index them for resolution.
            const auto existing = db.tree.find(package_segs);
            const bool isDup = existing.has_value();

            ModuleRec m{};
            m.file = file;
            m.package_path = db.pool.append(package_segs);
            m.leaf_name = leafOf(package_segs);
            m.loc = loc;

            m.import_begin = 0;
            m.import_count = 0;
            m.edge_begin = 0;
            m.edge_count = 0;

            m.unit_index = unit_index;
            m.arena_index = arena_index;
            m.valid = isDup ? 0u : 1u;

            db.modules.push_back(m);

            // Update file->module mapping if absent
            db.module_by_file.try_emplace(file, id);

            if (isDup)
            {
                db.errors.push_back(ModulePassError{
                    .kind = ModulePassErrKind::DuplicateModulePath,
                    .file = file,
                    .owner = kInvalidModule,
                    .existing = existing.value(),
                    .duplicate = id,
                    .import_id = static_cast<ImportId>(-1),
                    .loc = loc
                });
                return id; // keep record, but invalid & not resolvable
            }

            // Canonical insertion
            (void)db.tree.insert(package_segs, id);

            // Optional hash index (VALID only)
            {
                auto view = db.pool.view(db.modules[(size_t)id].package_path);
                const uint64_t h = hashPath(view);
                db.modules_by_hash[h].push_back(id);
            }

            return id;
        }

        void beginImports(ModuleId mid)
        {
            db.modules[(size_t)mid].import_begin = (uint32_t)db.imports.size();
            db.modules[(size_t)mid].import_count = 0;
        }

        void beginEdges(ModuleId mid)
        {
            db.modules[(size_t)mid].edge_begin = (uint32_t)db.graph.edges.size();
            db.modules[(size_t)mid].edge_count = 0;
        }

        ImportId addImport(ModuleId owner,
                           llvm::ArrayRef<lex::SymId> import_segs,
                           std::optional<lex::SymId> alias,
                           const lex::Loc& loc)
        {
            const ImportId iid = static_cast<ImportId>(db.imports.size());

            ImportRec r{};
            r.owner = owner;
            r.path = db.pool.append(import_segs);
            r.alias = alias;
            r.bound_name = alias.has_value() ? *alias : leafOf(import_segs);
            r.loc = loc;

            db.imports.push_back(r);
            db.modules[(size_t)owner].import_count++;

            return iid;
        }

        void addEdge(ModuleId from, ModuleId to, ImportId via)
        {
            if (to == kInvalidModule) return;
            db.graph.edges.push_back(to);
            db.graph.edge_import.push_back(via);
            db.modules[(size_t)from].edge_count++;
        }

        // Deterministic canonical resolution: use trie.
        ModuleId resolveModuleByPath(llvm::ArrayRef<lex::SymId> segs) const
        {
            auto hit = db.tree.find(segs);
            return hit.has_value() ? *hit : kInvalidModule;
        }

        // Optional alternate resolution via hash index (VALID-only), kept for debugging.
        ModuleId tryResolveModuleByPathHash(llvm::ArrayRef<lex::SymId> segs) const
        {
            const uint64_t h = hashPath(segs);
            auto it = db.modules_by_hash.find(h);
            if (it == db.modules_by_hash.end()) return kInvalidModule;

            for (ModuleId cand : it->second)
            {
                const auto& mr = db.modules[(size_t)cand];
                if (!mr.valid) continue;
                auto cand_segs = db.pool.view(mr.package_path);
                if (equalPath(cand_segs, segs))
                    return cand;
            }

            return kInvalidModule;
        }
    };

    // -------------------------------------------
    // Pass 1 runner
    // -------------------------------------------
    inline ModulePassDB runModulePass(hir::ArenaHolder& holder)
    {
        ModulePassBuilder b;
        b.db.modules.reserve(holder.arenas_.size());

        // Phase 1: register modules (canonical paths only)
        for (size_t i = 0; i < holder.arenas_.size(); ++i)
        {
            const auto fileId = static_cast<FileId>(i); // map to real file ids if needed
            const auto unitIndex = static_cast<uint32_t>(i);
            const auto arenaIndex = static_cast<uint32_t>(i);

            hir::Arena& ar = holder.arenas_[i];

            const llvm::ArrayRef<lex::SymId> module_segs =
                hir::getPathSegsFromExprPath(ar, ar.module.package_path);

            b.addModule(fileId, module_segs, unitIndex, arenaIndex, ar.module.loc);
        }

        // Phase 2: collect imports + validate bindings + resolve edges
        for (size_t i = 0; i < holder.arenas_.size(); ++i)
        {
            const FileId fileId = static_cast<FileId>(i);
            auto mid_it = b.db.module_by_file.find(fileId);
            if (mid_it == b.db.module_by_file.end())
                continue;

            const ModuleId mid = mid_it->second;
            b.beginImports(mid);
            b.beginEdges(mid);

            hir::Arena& ar = holder.arenas_[i];

            // Detect import binding collisions within this module.
            llvm::DenseMap<lex::SymId, ImportId> bound;

            // Also useful: module path segs for self-import check
            const auto self_segs = b.db.pool.view(b.db.modules[(size_t)mid].package_path);

            for (auto importId : ar.module.imports)
            {
                auto& imp = ar.imports[(size_t)importId];

                const llvm::ArrayRef<lex::SymId> import_segs =
                    hir::getPathSegsFromExprPath(ar, imp.path);

                const ImportId iid = b.addImport(mid, import_segs, imp.alias, imp.loc);

                // binding collision check (alias-or-leaf)
                const lex::SymId bn = b.db.imports[(size_t)iid].bound_name;
                if (bn != lex::SymId{})
                {
                    if (auto it = bound.find(bn); it != bound.end())
                    {
                        b.db.errors.push_back(ModulePassError{
                            .kind = ModulePassErrKind::DuplicateImportBinding,
                            .file = fileId,
                            .owner = mid,
                            .existing = kInvalidModule,
                            .duplicate = kInvalidModule,
                            .import_id = iid,
                            .loc = imp.loc
                        });
                        // Continue building DB for recovery; do not early-exit.
                    }
                    else
                    {
                        bound.try_emplace(bn, iid);
                    }
                }

                // self-import check
                if (equalPath(self_segs, import_segs))
                {
                    b.db.errors.push_back(ModulePassError{
                        .kind = ModulePassErrKind::SelfImport,
                        .file = fileId,
                        .owner = mid,
                        .existing = mid,
                        .duplicate = mid,
                        .import_id = iid,
                        .loc = imp.loc
                    });
                    // Continue; still attempt resolution below.
                }

                // resolve target (canonical trie-based)
                const ModuleId target = b.resolveModuleByPath(import_segs);
                b.db.imports[(size_t)iid].target = target;

                if (target == kInvalidModule)
                {
                    b.db.errors.push_back(ModulePassError{
                        .kind = ModulePassErrKind::UnknownImportTarget,
                        .file = fileId,
                        .owner = mid,
                        .existing = kInvalidModule,
                        .duplicate = kInvalidModule,
                        .import_id = iid,
                        .loc = imp.loc
                    });
                }

                b.addEdge(mid, target, iid);
            }
        }

        return std::move(b.db);
    }
} // namespace sema

#endif // INZ_MODULE_IMPORT_PASS_HPP
