//
// Created by yhwach on 10/2/25.
//

#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <token.hpp>
#include "ast/nodes/type/type.hpp"

#include "decl.hpp"

namespace sema {
    enum class SymbolKind : uint8_t {
        Var, Param, Field, Func, TypeAlias, Struct, Enum, Trait,
        Module, Namespace, ImportAlias, Const
    };

    enum class Visibility : uint8_t { Private, Public };

    enum class Mutability : uint8_t { Imm, Mut };

    enum class Storage : uint8_t { Auto, Static };

    struct Symbol {
        lex::SymId id;
        SymbolKind kind;
        lex::Loc loc;
        uint32_t scope_depth = 0;
        ast::Type *type = nullptr;

        const ast::Decl *decl = nullptr;
        Visibility vis = Visibility::Private;
        Mutability mutability = Mutability::Imm;
        Storage storage = Storage::Auto;

        uint32_t overload_index = 0;

        uint64_t uid = 0;

        ~Symbol() {
            delete type;
        }
    };
}

#endif //SYMBOL_HPP
