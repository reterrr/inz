//
// Created by yhwach on 8/21/25.
//

#ifndef VISITABLE_HPP
#define VISITABLE_HPP

namespace ast {
    template<typename V>
    struct Visitable {
        virtual ~Visitable() = default;

        virtual void accept(V &) = 0;
    };
}

#endif //VISITABLE_HPP
