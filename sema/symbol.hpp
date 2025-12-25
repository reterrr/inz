//
// Created by yhwach on 10/2/25.
//

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <token.hpp>

namespace sema
{
    enum class SymbolKind : uint8_t
    {
        Var, Param, Field, Func, TypeAlias, Struct, Enum, Trait
    };

    enum class Visibility : uint8_t { Private, Public };

    enum class Mutability : uint8_t { Imm, Mut };

    enum class Storage : uint8_t { Auto, Static };

    struct VarInfo final
    {
        ast::VarStmt* decl_ = nullptr;

    };

    struct Symbol
    {
        lex::SymId id;
        SymbolKind kind;
        lex::Loc loc;
        uint32_t scope_depth = 0;

        Visibility vis = Visibility::Private;
        Mutability mutability = Mutability::Imm;

        uint64_t uid = 0;

        ~Symbol()
        = default;
    };
}

#endif //SYMBOL_HPP
