//
// Created by yhwach on 8/29/25.
//

#ifndef VISITOR_HPP
#define VISITOR_HPP

namespace ast::visitor
{
    template <typename T>
    struct VisitSlot
    {
        virtual ~VisitSlot() = default;
        virtual void visit(T&) = 0;
    };

    template <typename... Ts>
    struct Visitor : VisitSlot<Ts>...
    {
        using VisitSlot<Ts>::visit...;

        ~Visitor() override = default;
    };
}

#endif //VISITOR_HPP
