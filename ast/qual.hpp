//
// Created by yhwach on 8/20/25.
//

#ifndef QUAL_HPP
#define QUAL_HPP
#include <cstdint>

namespace ast::qual {
    enum class TypeQual : uint8_t {
        qual_none = 0,
        qual_mut = 1 << 0,
        qual_const = 1 << 1, // compile-time constant
    };

    constexpr TypeQual operator|(TypeQual a, TypeQual b);
}


#endif //QUAL_HPP
