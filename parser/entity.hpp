//
// Created by yhwach on 8/17/25.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <vector>

namespace parser {
    enum class entity_type;
    class compound;

    class entity {
        const entity_type entity_type_;
        compound *owner_{nullptr};
        Type *type_{nullptr};
        const entity *parent_{nullptr};
        std::vector<entity *> children_{nullptr};

    public:
        virtual ~entity() = default;

        [[nodiscard]]
        entity_type type() const {
            return entity_type_;
        }

        [[nodiscard]]
        const compound *owner() const {
            return owner_;
        }

    protected:
        explicit entity(const entity_type type)
            : entity_type_(type) {
        }

    private:
        void owner(compound *owner) {
            owner_ = owner;
        }

        friend class compound;
    };
}

#endif //ENTITY_HPP
