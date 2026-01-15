//
// Created by yhwach on 12/30/25.
//

#ifndef INZ_NEW_SCOPE_HPP
#define INZ_NEW_SCOPE_HPP

#include "module_import_pass.hpp"


namespace sema
{
    enum class SymKind : uint8_t { Fn, LoadFn, Struct, Trait, TypeAlias };
    struct Symbol
    {
        SymKind kind{};
        uint32_t id{};
        uint8_t arity{};    // generic arity for types (0 for values)
        lex::Loc loc{};
        bool exported{};
        bool intrinsic{};
    };

    struct ModuleScope
    {
        llvm::DenseMap<lex::SymId, ImportBinding> imports; // bound name -> import binding
        llvm::DenseMap<lex::SymId, Symbol> types; // type namespace
        llvm::DenseMap<lex::SymId, Symbol> values; // value namespace
        llvm::SmallVector<ImplId, 4> impls; // impl blocks in this module
    };

    struct ScopePassDB
    {
        std::

    };

    ScopePassDB runScopePass()
    {
    }
}
#endif //INZ_NEW_SCOPE_HPP
