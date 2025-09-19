//
// Created by yhwach on 9/1/25.
//

#ifndef MODULE_HPP
#define MODULE_HPP

#include "../../node.hpp"
#include "../visit/visitable.hpp"

#include "../visit/module_visitor.hpp"

namespace ast {
    struct Module final : Node, Visitable<visitor::ModuleVisitor> {
        using Node::Node, Visitable::accept;

        std::vector<lex::SymId> package_path; // may be empty
        std::vector<ImportDecl *> imports;
        std::vector<Decl *> decls; // functions, types, globals, ...

        Module(std::vector<lex::SymId> pkg,
               std::vector<ImportDecl *> imps,
               std::vector<Decl *> ds,
               const lex::Loc &L)
            : Node(NodeKind::Decl_Module, L),
              package_path(std::move(pkg)),
              imports(std::move(imps)),
              decls(std::move(ds)) {
        }

        void accept(visitor::ModuleVisitor &v) override;
    };

    inline void Module::accept(visitor::ModuleVisitor &v) {
        v.visit(*this);
    }

    typedef Module *ModulePtr;
}

#endif //MODULE_HPP
