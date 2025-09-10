//
// Created by yhwach on 8/29/25.
//

#ifndef VISITOR_HPP
#define VISITOR_HPP

namespace ast::visitor {
    template<typename T>
    struct VisitSlot {
        virtual void visit(T &) {
        }
    };

    template<typename... Ts>
    struct Visitor : VisitSlot<Ts>... {
        using VisitSlot<Ts>::visit...;

        virtual ~Visitor() = default;
    };

    template<>
    struct Visitor<> {

    };
}

#endif //VISITOR_HPP
