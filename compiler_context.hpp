//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_COMPILER_CONSTEXT_HPP
#define INZ_COMPILER_CONSTEXT_HPP
#include <filesystem>
#include <vector>

#include "ast.hpp"
#include "interner.hpp"

struct CompilerContext
{
    ast::Ast ast; // basically just factory
    ast::Interner<> stringInterner;
    ast::Interner<> identInterner;
    ast::Interner<> numericInterner;

    std::vector<std::filesystem::path> files;
};

#endif //INZ_COMPILER_CONSTEXT_HPP
