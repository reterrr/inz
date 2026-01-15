//
// Created by yhwach on 12/25/25.
//

#ifndef INZ_MODULE_GRAPH_HPP
#define INZ_MODULE_GRAPH_HPP

#include <cassert>

#include "module_import_pass.hpp"
#include "hir/arena.hpp"
#include "hir/modules.hpp"
#include "hir/visitor.hpp"

namespace sema
{
    template <typename It>
    struct ModuleCoreVisitor final : hir::Visitor<It>
    {
        using hir::Visitor<It>::Visitor;
        using hir::Visitor<It>::visit;
        using hir::Visitor<It>::it_;

        explicit ModuleCoreVisitor(It& it)
            : hir::Visitor<It>(it)
        {
        }

        void visit(hir::Module& module) override
        {
            // then imports
            for (auto imp_id : module.imports)
            {
                it_.defer(hir::ArenaKinds::imports, imp_id);
            }

            it_.defer(hir::ArenaKinds::exprs, module.package_path);
        }

        void visit(hir::Import& import) override
        {
            it_.defer(hir::ArenaKinds::exprs, static_cast<uint32_t>(import.path));
        }

        template <typename T>
        void visit(T&)
        {
        }
    };

    template <class IteratorT>
    struct ModuleImportApplyVisitor : hir::Visitor<IteratorT>
    {
        using hir::Visitor<IteratorT>::Visitor;
        using hir::Visitor<IteratorT>::visit;
        using hir::Visitor<IteratorT>::it_;

        hir::Arena& arena_;
        const std::vector<hir::ModuleId>& import_owner_;
        hir::pass::ModuleImportPassResult& out_;

        ModuleImportApplyVisitor(IteratorT& it,
                                 hir::Arena& arena,
                                 const std::vector<hir::ModuleId>& import_owner,
                                 hir::pass::ModuleImportPassResult& out)
            : hir::Visitor<IteratorT>(it), arena_(arena), import_owner_(import_owner), out_(out)
        {
        }

        void visit(hir::Module& m)
        {
            auto& i = arena_.exprs[m.package_path];
            auto s = std::get<hir::ExprPath>(i.kind);
            s.path;
            auto& rec = out_.modules[mid];
            rec.id = mid;
            rec.loc = m.loc;
            rec.package_path = m.package_path;
            // imports will be filled when Import nodes are visited
        }

        void visit(hir::Import& imp)
        {
            const auto iid =
                static_cast<hir::ImportId>(&imp - arena_.imports.data());

            assert(iid < import_owner_.size() &&
                "import owner precompute out of range");
            const hir::ModuleId mid = import_owner_[iid];

            auto& mrec = out_.modules[mid];
            mrec.imports.push_back(
                hir::pass::ImportRecord{
                    .id = iid,
                    .loc = imp.loc,
                    .path = imp.path,
                    .alias = imp.alias
                });
        }

        template <class T>
        void visit(T&)
        {
            // ignore other nodes
        }
    };

    using ModuleIterator = hir::Iterator<
        ModuleCoreVisitor,
        ModuleImportApplyVisitor,
        hir::ArenaKinds,
        uint32_t,
        hir::Arena,
        &hir::Arena::module,
        &hir::Arena::imports,
        &hir::Arena::tparams,
        &hir::Arena::params,
        &hir::Arena::field_decls,
        &hir::Arena::field_inits,
        &hir::Arena::decls,
        &hir::Arena::types,
        &hir::Arena::exprs,
        &hir::Arena::stmts,
        &hir::Arena::blocks
    >;
}

#endif //INZ_MODULE_GRAPH_HPP
