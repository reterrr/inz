#ifndef SCOPEINFO_HPP
#define SCOPEINFO_HPP

#include <cstdint>
#include <utility>
#include <vector>

#include "symbol_table.hpp"

namespace sema::scope
{
    using ScopeId = uint32_t;

    enum class ScopeKind { Project, Module, Function, Anon, Struct, If, ElseIf, Else, While, DoWhile };

    struct Scope
    {
        ScopeId id_; // e
        ScopeId parentId_; // d
        std::vector<ScopeId> path_; // a.b.c.d
        std::vector<ScopeId> children_;
        SymbolTable symbolTable_;
        ScopeKind kind_;

        Scope(ScopeId id, ScopeId parent_id,
              std::vector<ScopeId> path,
              std::vector<ScopeId> children,
              SymbolTable symbolTable,
              ScopeKind kind)
            : id_(id),
              parentId_(parent_id),
              path_(std::move(path)),
              children_(std::move(children)),
              symbolTable_(std::move(symbolTable)),
              kind_(kind)
        {
        }
    };


    struct ProjectScope
    {
        std::vector<Scope> moduleScopes;
    };
}


#endif
