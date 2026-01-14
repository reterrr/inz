cmake_minimum_required(VERSION 3.30)
project(inz LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE FILEPATH "C++ compiler")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED)
find_package(Boost REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(Eigen3 REQUIRED)

set(TOKEN_DIR ${CMAKE_SOURCE_DIR}/tokens)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_BUILD_TYPE DEBUG)

include_directories(
        ./
        generated
        ast
        ast/nodes
        parser
        lexer
        lexer/generated
)

#option(ENABLE_ASAN "Enable AddressSanitizer + LeakSanitizer" ON)
#
#if(ENABLE_ASAN)
#    # Works best with Clang. You already force clang++.
#    add_compile_options(
#            -O1
#            -g
#            -fno-omit-frame-pointer
#            -fno-optimize-sibling-calls
#            -fsanitize=address
#    )
#    add_link_options(-fsanitize=address)
#
#    # LeakSanitizer is included in ASan on Linux/Clang; detect_leaks controls it at runtime.
#    # If you ever need it explicitly:
#    # add_compile_options(-fsanitize=leak)
#    # add_link_options(-fsanitize=leak)
#endif()

add_executable(inz main.cpp
        #        lexer/lexer.cpp
        generated/lexer/lexer.yy.cpp
        parser/parser.cpp
        ast/node_type.hpp
        ast/node.hpp
        #        sema/type/type.hpp
        ast/nodes/expr/expr.hpp
        ast/nodes/visit/visitable.hpp
        ast/nodes/visit/expr_visitor.hpp
        ast/nodes/expr/int_literal_expr.hpp
        ast/nodes/expr/float_literal_expr.hpp
        ast/nodes/expr/unary_op_expression_kind.hpp
        ast/nodes/expr/binary_op_exression_kind.hpp
        ast/nodes/expr/unary_op_expr.hpp
        ast/nodes/expr/binary_op_expr.hpp
        ast/nodes/visit/overallvisitor.cpp
        ast/ast.hpp
        ast/nodes/expr/ref_expr.hpp
        ast/nodes/decl/decl.hpp
        ast/nodes/decl/param_decl.hpp
        ast/nodes/stmt/statement.hpp
        ast/nodes/stmt/block_statement.hpp
        ast/nodes/stmt/return_statement.hpp
        ast/nodes/stmt/if_statement.hpp
        ast/nodes/stmt/while_statement.hpp
        ast/nodes/stmt/var_statement.hpp
        ast/nodes/visit/decl_visitor.hpp
        ast/nodes/visit/stmt_visitor.hpp
        ast/nodes/visit/visitor.hpp
        ast/nodes/expr/bool_literal_expr.hpp
        ast/nodes/expr/field_init_expr.hpp
        ast/nodes/module/module.hpp
        ast/nodes/visit/module_visitor.hpp
        ast/ast.cpp
        ast/nodes/expr/assign_expr.hpp
        ast/nodes/stmt/expr_statement.hpp
        ast/nodes/stmt/continue_statement.hpp
        ast/nodes/stmt/break_statement.hpp
        ast/nodes/stmt/do_while_statement.hpp
        ast/nodes/module/import_decl.hpp
        ast/nodes/expr/field_expr.hpp
        ast/nodes/expr/call_expr.hpp
        ast/nodes/expr/index_expr.hpp
        ast/ast_iterator.hpp
        ast/nodes/visit/dump_visitor.hpp
        ast/nodes/decl/struct_decl.hpp
        ast/nodes/decl/field_decl.hpp
        #        sema/passes/scope_pass.cpp
        #        sema/symbol_table.hpp
        #        sema/passes/pass.hpp
        #        sema/passes/decl_pass.hpp
        #        sema/passes/decl_pass.cpp
        #        ast/nodes/visit/overallvisitor.cpp
        #        ast/nodes/visit/overallvisitor.hpp
        #        sema/scope_stack.hpp
        #        sema/symbol.hpp
        #        sema/type_interner.hpp
        #        sema/sema.hpp
        ast/nodes/visit/project_visitor.hpp
        ast/nodes/expr/type_expr.hpp
        ast/nodes/expr/array_type_expr.hpp
        ast/nodes/expr/path_type_expr.hpp
        ast/nodes/expr/ref_type_expr.hpp
        ast/nodes/expr/builtin_type_expr.hpp
        ast/nodes/expr/char_literal_expr.hpp
        ast/nodes/expr/literal_expr.hpp
        ast/nodes/expr/string_literal_expr.hpp
        ast/nodes/expr/array_literal_expr.hpp
        #test/test.cpp
        ast/nodes/expr/path_expr.hpp
        ast/nodes/expr/cast_expr.hpp
        ast/nodes/stmt/else_if_statement.hpp
        ast/nodes/stmt/else_statement.hpp
        ast/interner.hpp
        ast/nodes/type/type_parametrized_decl.hpp
        ast/nodes/type/type_arged_expr.hpp
        #        sema/passes/module_pass.cpp
        #        sema/passes/module_pass.hpp
        compiler_context.hpp
        project_loader.hpp
        translation.hpp
        ast/nodes/stmt/block_stmt_kind.hpp
        ast/nodes/decl/field_visibility.hpp
        ast/nodes/stmt/var_mutablity_storage.hpp
        ast/nodes/expr/assign_op.hpp
        ast/nodes/expr/type_expr_kind.hpp
        sema/module_graph.hpp
        sema/module_import_pass.hpp

        sema/path_pool.hpp
        sema/module_builder_pass.hpp

        sema/scope_pass.hpp

        ast/nodes/decl/fn_header.hpp
        ast/nodes/decl/fn_decl.hpp


        sema/decl_bind_pass.hpp
        sema/name_resolution_pass.hpp


        sema/type_formation_pass.hpp
        sema/dump_module_tree.hpp
        compilation_contoller.hpp
        sema/body_type_check_pass.hpp
        ast/nodes/decl/load_fn_decl.hpp
        pre_assign_controller.hpp
        sema/prep_pass.hpp
        sema/module_pass.hpp

        sema/prelude_injector.hpp
        sema/db_printer.hpp
        sema/new_scope.hpp

        sema/type_lower_pass.hpp
        reserved/parser.cpp
        sema_rec/pass2.hpp
        sema_rec/pass2.cpp
        sema_rec/pass_3.5.hpp
        sema_rec/pass_3.5.cpp
        sema_rec/pass3.hpp
        sema_rec/pass3.cpp
        sema_rec/pass4.hpp
        sema_rec/pass4.cpp
        sema_rec/pass_4.5.hpp
        sema_rec/pass_4.5.cpp
        sema_rec/pass5_reserved.hpp
        sema_rec/pass5_reserved.cpp
        sema_rec/type_system.hpp
        sema_rec/pass5.hpp
        sema_rec/pass5.cpp
        sema_rec/pass6.hpp
        sema_rec/pass6.cpp
        sema_rec/pass7.hpp
        sema_rec/pass7.cpp
        sema_rec/pass8.hpp
        sema_rec/pass8.cpp
        sema_rec/pass9_1_bootstrap.hpp
        sema_rec/pass9_1_bootstrap.cpp
        sema_rec/pass9_2_declare_user_fns.hpp
        sema_rec/pass9_2_declare_user_fns.cpp
        sema_rec/pass9_3_declare_load_fns.hpp
        sema_rec/pass9_3_declare_load_fns.cpp
        sema_rec/pass9_5_codegen_bodies.hpp
        sema_rec/pass9_5_codegen_bodies.cpp
        sema_rec/pass9_6_literals.hpp
        sema_rec/pass9_6_literals.cpp
        sema_rec/pass9_7_ops.hpp
        sema_rec/pass9_7_ops.cpp
        sema_rec/pass9_4.hpp
        sema_rec/pass9_4.cpp
        sema_rec/pass11.hpp
        sema_rec/pass11.cpp
        sema_rec/pipeline_gate.hpp
        sema_rec/reserved_struct.hpp
        sema_rec/pass12_execute.hpp
        sema_rec/pass12_execute.cpp
        runtime.hpp
        runtime.cpp
        sema_rec/runtime_intrinsics.hpp
        sema_rec/logging_entities.hpp
        sema_rec/sym_kind.hpp
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
target_link_libraries(inz PRIVATE LLVM Eigen3::Eigen)
target_link_options(inz PRIVATE "-Wl,--export-dynamic")