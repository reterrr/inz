//
// Created by yhwach on 12/21/25.
//

#ifndef INZ_COMPILATION_HPP
#define INZ_COMPILATION_HPP
#include <vector>

#include "ast/ast.hpp"


struct Unit final
{
    ast::ModulePtr module;

    // std::size_t node_count_ = 0;
    // std::size_t expr_count_ = 0;
    // std::size_t stmt_count_ = 0;
    // std::size_t decl_count_ = 0;
    // std::size_t type_count_ = 0; // add if you have TypeExpr base
    // std::size_t module_count_ = 0;
};

class Translation final
{
public:
    std::vector<Unit> units;


    void addModule(ast::ModulePtr module)
    {
        units.emplace_back(module);
    }
};

#endif //INZ_COMPILATION_HPP
