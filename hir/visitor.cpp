//
// Created by yhwach on 12/24/25.
//


#include "hir/decls.hpp"
#include "visitor.hpp"
#include "iterator.hpp"


hir::Visitor::Visitor(::hir::Iterator& it)
    : iterator(it)
{
}

void hir::Visitor::visit(Decl& decl)
{
    std::visit([this](auto&& a)
    {
        visit(a);
    }, decl.kind);
}
