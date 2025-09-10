//
// Created by yhwach on 8/18/25.
//

#ifndef COMPOUND_TYPE_HPP
#define COMPOUND_TYPE_HPP
#include <cstdint>

namespace parser {
    enum class compound_type : std::uint8_t {
        file_,
        struct_,
        enum_,
    };
}

#endif //COMPOUND_TYPE_HPP
