//
// Created by yhwach on 8/16/25.
//

#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstdint>
#include <string>
#include <variant>

// this will be builtin type in my language
struct magic_int
{
};

// this will user obj literal like: { int, int, int, string }
struct user_obj
{
};

typedef int64_t kl_int;
typedef magic_int kl_magic_int;
typedef std::string* kl_string; //should be pointer?
typedef double kl_float;
typedef bool kl_bool;
typedef char kl_char;

typedef user_obj kl_user_obj;

typedef std::variant<std::monostate,
                     kl_int,
                     kl_magic_int,
                     kl_string,
                     kl_float,
                     kl_bool,
                     kl_char,
                     kl_user_obj> kl_literal;

enum class kl_type : uint8_t
{
    kl_int,
    kl_magic_int,
    kl_bigint,
    kl_string,
    kl_double,
    kl_bool,
    kl_char,

    kl_callable,
    kl_user
};

enum class kl_builtin_type : uint8_t
{
    kl_int,
    kl_magic_int,
    kl_string,
    kl_double,
    kl_bool,
    kl_char
};

#endif //TYPES_HPP
