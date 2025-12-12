//
// Created by yhwach on 11/28/25.
//

#ifndef INZ_SCOPE_GUARD_HPP
#define INZ_SCOPE_GUARD_HPP
#include "scope_stack.hpp"


class ScopeGuard final
{
    sema::ScopeController& controller_;
    size_t popCounter_;

public:
    explicit ScopeGuard(sema::ScopeController& controller)
        : controller_(controller),
          popCounter_(controller_.stackSize())
    {
    }

    ~ScopeGuard()
    {
        for (auto i = controller_.stackSize() - popCounter_; i > 0; --i)
            controller_.exitScope();
    }
};


#endif //INZ_SCOPE_GUARD_HPP
