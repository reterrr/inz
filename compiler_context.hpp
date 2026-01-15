//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_COMPILER_CONSTEXT_HPP
#define INZ_COMPILER_CONSTEXT_HPP
#include <filesystem>
#include <vector>

#include "interner.hpp"

struct CompilerContext
{
    ast::Interner<> stringInterner;
    ast::Interner<> identInterner;
    ast::Interner<> numericInterner;

    std::vector<std::filesystem::path> files;
};

#endif //INZ_COMPILER_CONSTEXT_HPP
