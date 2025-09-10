#include "qual.hpp"
//
// Created by yhwach on 8/21/25.
//

using ast::qual::TypeQual;

TypeQual ast::qual::operator|(TypeQual a, TypeQual b) {
    return static_cast<TypeQual>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b)
    );
}
