#ifndef SCOPE_STACK_HPP
#define SCOPE_STACK_HPP

#include <limits>
#include <stack>

#include "helper.hpp"
#include "symbol_table.hpp"
#include "scope_info.hpp"
#include "scope_to_symbol_map.hpp"

#include <llvm/Support/ErrorHandling.h>

namespace sema
{
    struct AnonymousScopeTag
    {
    };

    class ScopeController final
    {
        inline static ScopeId counter = 1;

        scope::Scope2SymbolMap& map;
        std::stack<ScopeId> stack_;
        std::vector<scope::Scope>& scopeTable_;

    public:
        ScopeController(scope::Scope2SymbolMap& map,
                        std::vector<scope::Scope>& scope_table)
            : map(map),
              scopeTable_(scope_table)
        {
        }

        scope::ScopeId enterProject()
        {
            ScopeId id = counter;

            scopeTable_.emplace_back(id,
                                     0,
                                     helper::stackToVector(stack_),
                                     std::vector<ScopeId>{},
                                     SymbolTable{},
                                     scope::ScopeKind::Project);

            stack_.push(id);
            ++counter;

            return id;
        }

        [[nodiscard]]
        size_t stackSize() const
        {
            return stack_.size();
        }

        [[nodiscard]]
        scope::ScopeId current() const
        {
            return stack_.top();
        }

        scope::ScopeId enterScope(lex::SymId symbolId, scope::ScopeKind kind)
        {
            if (counter == std::numeric_limits<decltype(counter)>::max())
                llvm::reportFatalInternalError("ScopeId counter overflow");

            map.add(counter, symbolId);

            return _enterScope(kind);
        }

        scope::ScopeId enterScope(AnonymousScopeTag, scope::ScopeKind kind)
        {
            if (counter == std::numeric_limits<decltype(counter)>::max())
                llvm::reportFatalInternalError("ScopeId counter overflow");

            return _enterScope(kind);
        }

        scope::ScopeId enterScope(const std::vector<lex::SymId>& symbols, scope::ScopeKind kind)
        {
            if (counter > std::numeric_limits<decltype(counter)>::max() - symbols.size())
                llvm::reportFatalInternalError("ScopeId counter overflow");

            ScopeId last = 0;
            std::ranges::for_each(
                symbols.begin(),
                symbols.end(),
                [this, kind, &last](lex::SymId symId)
                {
                    auto scopeId = _enterScope(kind);
                    map.add(scopeId, symId);
                    last = scopeId;
                }
            );

            return last;
        }

        void exitScope()
        {
            stack_.pop();
        }

    private:
        scope::ScopeId _enterScope(scope::ScopeKind kind)
        {
            ScopeId parentId = stack_.top();
            ScopeId id = counter;

            scopeTable_.emplace_back(id,
                                     parentId,
                                     helper::stackToVector(stack_),
                                     std::vector<ScopeId>{},
                                     SymbolTable{},
                                     kind);

            scopeTable_[parentId - 1].children_.push_back(id);

            stack_.push(id);
            ++counter;

            return id;
        }
    };
}

#endif
