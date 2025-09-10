//
// Created by yhwach on 8/17/25.
//

#ifndef EXPR_HPP
#define EXPR_HPP

#include "entity.hpp"

namespace parser {
    struct expr : entity {
        using entity::entity;

        virtual void accept(struct expr_visitor &v) = 0;
    };

    struct expr_int final : expr {
        kl_int v;

        void accept(expr_visitor &v) override;
    };

    struct expr_float final : expr {
        kl_float v;

        void accept(expr_visitor &v) override;
    };

    struct expr_bool final : expr {
        kl_bool v;

        void accept(expr_visitor &v) override;
    };

    struct expr_string final : expr {
        kl_string v;

        void accept(expr_visitor &v) override;
    };
}


#endif //EXPR_HPP
