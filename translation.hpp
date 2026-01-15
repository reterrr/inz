//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_COMPILATION_HPP
#define INZ_COMPILATION_HPP
#include <vector>

#include "ast/ast.hpp"

class Translation final
{
public:
    std::vector<ast::Ast> units;

    void addModule(ast::Ast&& unit)
    {
        units.emplace_back(std::move(unit));
    }
};

#endif //INZ_COMPILATION_HPP
