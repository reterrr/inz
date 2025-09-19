//
// Created by yhwach on 8/21/25.
//

#ifndef VISITABLE_HPP
#define VISITABLE_HPP

namespace ast {
    namespace visitor {
        struct DumpVisitor;
    }

    template<typename V>
    struct Visitable {
        virtual ~Visitable() = default;

        virtual void accept(V &) = 0;
    };

    template<>
    struct Visitable<visitor::DumpVisitor> {
        virtual ~Visitable() = default;

        virtual void accept(const visitor::DumpVisitor &) const = 0;
    };
}

#endif //VISITABLE_HPP
