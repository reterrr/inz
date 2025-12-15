cmake_minimum_required(VERSION 3.30)
project(inz LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE FILEPATH "C++ compiler")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(Boost REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(TOKEN_DIR ${CMAKE_SOURCE_DIR}/tokens)
set(TEMPLATES_DIR ${CMAKE_SOURCE_DIR}/templates)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_BUILD_TYPE DEBUG)

include_directories(
        generated
        ast
        ast/nodes
        parser
        lexer
        lexer/generated
)

add_executable(inz main.cpp
        lexer/lexer.cpp
        generated/lexer/lexer.yy.cpp
        parser/parser.cpp
        ast/node_type.hpp
        ast/node.hpp
        ast/nodes/type/type.hpp
        ast/nodes/expr/expr.hpp
        ast/nodes/visit/visitable.hpp
        ast/nodes/visit/expr_visitor.hpp
        ast/nodes/expr/int_expr.hpp
        ast/nodes/expr/float_expr.hpp
        ast/nodes/expr/unary_op_expression_kind.hpp
        ast/nodes/expr/binary_op_exression_kind.hpp
        ast/nodes/expr/unary_op_expr.hpp
        ast/nodes/expr/binary_op_expr.hpp
        ast/ast.hpp
        ast/allocator.hpp
        ast/nodes/expr/ref_expr.hpp
        ast/nodes/decl/function_decl.hpp
        ast/nodes/decl/decl.hpp
        ast/nodes/decl/param_decl.hpp
        ast/nodes/stmt/statement.hpp
        ast/nodes/stmt/block_statement.hpp
        ast/nodes/stmt/return_statement.hpp
        ast/nodes/stmt/if_statement.hpp
        ast/nodes/stmt/while_statement.hpp
        ast/nodes/stmt/var_decl_statement.hpp
        ast/nodes/visit/decl_visitor.hpp
        ast/nodes/visit/stmt_visitor.hpp
        ast/nodes/visit/visitor.hpp
        ast/nodes/expr/bool_expr.hpp
        ast/nodes/expr/string_expr.hpp
        ast/nodes/expr/obj_expr.hpp
        ast/nodes/expr/field_init_expr.hpp
        ast/nodes/module/module.hpp
        ast/nodes/visit/module_visitor.hpp
        ast/ast.cpp
        ast/nodes/expr/assign_expr.hpp
        ast/nodes/stmt/expr_statement.hpp
        ast/nodes/stmt/continue_statement.hpp
        ast/nodes/stmt/break_statement.hpp
        ast/nodes/stmt/do_while_statement.hpp
        ast/nodes/decl/type_alias_decl.hpp
        ast/nodes/module/import_decl.hpp
        ast/nodes/decl/var_decl.hpp
        ast/nodes/expr/field_expr.hpp
        ast/nodes/expr/init_declarator_expr.hpp
        ast/nodes/expr/call_expr.hpp
        ast/nodes/expr/index_expr.hpp
        ast/ast_iterator.hpp
        ast/nodes/project.hpp
        ast/nodes/visit/dump_visitor.hpp
        ast/nodes/decl/struct_decl.hpp
        ast/nodes/decl/field_decl.hpp
        hir/hir.hpp
        sema/passes/scope_pass.cpp
        sema/symbol_table.hpp
        hir/de_sugar.hpp
        sema/passes/pass.hpp
        sema/passes/decl_pass.hpp
        sema/passes/decl_pass.cpp
        ast/nodes/visit/overallvisitor.cpp
        ast/nodes/visit/overallvisitor.hpp
        sema/scope_stack.hpp
        sema/symbol.hpp
        sema/type_interner.hpp
        sema/sema.cpp
        sema/sema.hpp
        ast/nodes/visit/project_visitor.hpp
        ast/nodes/expr/type_expr.hpp
        ast/nodes/expr/array_type_expression.hpp
        ast/nodes/expr/path_type_expr.hpp
        ast/nodes/expr/ref_type_expr.hpp
        ast/nodes/expr/builtin_type_expr.hpp
)

target_include_directories(inz PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/parser
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/generated
        ${CMAKE_CURRENT_SOURCE_DIR}/ast
        ${CMAKE_CURRENT_SOURCE_DIR}/ast/nodes
        ${CMAKE_CURRENT_SOURCE_DIR}/ast/nodes/decl
        ${LLVM_INCLUDE_DIRS}
)
add_definitions(${LLVM_DEFINITIONS})


#target_link_libraries(inz PRIVATE parser_obj lexer_obj)
target_link_libraries(inz PRIVATE LLVMSupport)