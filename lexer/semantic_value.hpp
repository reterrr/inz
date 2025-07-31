#ifndef SEMANTIC_VALUE_HPP
#define SEMANTIC_VALUE_HPP

#include <string>
#include <variant>

typedef __int128 kl_bigint;
typedef __int64_t kl_int;
typedef bool kl_bool;
typedef std::string kl_string;

using SemanticValue = std::variant<
    std::monostate,
    kl_bool,

    kl_int,
    kl_bigint,

    kl_string
>;

#endif //SEMANTIC_VALUE_HPP
