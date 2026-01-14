#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "sema_rec/pipeline_gate.hpp" // LogSequence gate only

#include "compilation_contoller.hpp"
#include "compiler_context.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "reserved/parser.hpp"

#include "sema_rec/pass11.hpp"
#include "sema_rec/pass12_execute.hpp"
#include "sema_rec/pass2.hpp"
#include "sema_rec/pass3.hpp"
#include "sema_rec/pass4.hpp"
#include "sema_rec/pass5.hpp"
#include "sema_rec/pass5_reserved.hpp"
#include "sema_rec/pass6.hpp"
#include "sema_rec/pass7.hpp"
#include "sema_rec/pass8.hpp"
#include "sema_rec/pass9_1_bootstrap.hpp"
#include "sema_rec/pass9_2_declare_user_fns.hpp"
#include "sema_rec/pass9_3_declare_load_fns.hpp"
#include "sema_rec/pass9_5_codegen_bodies.hpp"
#include "sema_rec/pass9_6_literals.hpp"
#include "sema_rec/pass9_7_ops.hpp"
#include "sema_rec/pass_3.5.hpp"
#include "sema_rec/pass_4.5.hpp"

#include "ast/nodes/visit/dump_visitor.hpp"

#include <llvm/Support/raw_ostream.h>

namespace sema
{
    inline void dump_llvm_ir(std::ostream& os, const Pass9_1Result& st)
    {
        if (!st.module)
        {
            os << "[llvm] <no module>\n";
            return;
        }

        os << "----- LLVM IR: module '" << st.module->getName().str() << "' -----\n";
        st.module->print(llvm::outs(), nullptr);
        os << "\n----- end LLVM IR -----\n";
    }
}

int main()
{
    CompilerContext compilerContext;
    CompilationController controller;

    std::string err;
    if (!controller.loadConfiguration("./validate.toml", err))
    {
        std::cerr << err << '\n';
        return 1;
    }

    const auto config = controller.config;
    const auto dirPath = config.files.filesDir;
    const auto& libs = config.link.libs;

    DriverFlag driverFlags = DriverFlag::None;
    if (auto it = config.flags.presets.find("no-args"); it != config.flags.presets.end())
        driverFlags = it->second;

    Translation translation;
    Translation reserved_translation;

    // ---------------- parse user files ----------------
    for (const auto& file : std::filesystem::directory_iterator(dirPath))
    {
        std::ifstream in{file.path()};
        if (!in)
        {
            std::cerr << "Could not open file: " << file.path() << "\n";
            return 1;
        }

        Scanner scanner{compilerContext, &in};
        ast::Ast ast;
        yy::parser p{scanner, ast, translation, std::string_view{file.path().c_str()}};

        if (const int rc = p.parse(); rc != 0)
        {
            std::cerr << "Parse failed: " << file.path() << "\n";
            return 1;
        }
    }

    if (has_flag(driverFlags, DriverFlag::DumpAst))
    {
        for (const auto& unit : translation.units)
        {
            if (!unit.module_) continue;
            ast::visitor::DumpVisitor v{std::cout, compilerContext};
            v.visit(*unit.module_);
            std::cout << "\n";
        }
    }

    // ---------------- parse reserved builtins ----------------
    static constexpr auto kReservedSrc = R"(
        package builtin;

        struct Box<T>;


        fn box_new<T>(count: i64) -> Box::<T>;

        fn box_len<T>(b: &Box::<T>) -> i64;
        fn box_get<T>(b: &Box::<T>, i: i64) -> T;
        fn box_set<T>(b: &mut Box::<T>, i: i64, v: T) -> void;

        fn print<T>(t: &T) -> void;
        fn nl() -> void;
        fn put<T>(t: &T) -> void;
    )";

    {
        ast::Ast ast_for_reserved;
        std::istringstream in{kReservedSrc};
        Scanner scanner{compilerContext, &in};
        yy::reserved::parser p{scanner, ast_for_reserved, reserved_translation, "__builtin__.lang"};

        if (const int rc = p.parse(); rc != 0)
        {
            std::cerr << "Reserved parser failed (this should never happen).\n";
            return 1;
        }
    }

    // ---------------- intern key identifiers ----------------
    const auto sym_Box = compilerContext.identInterner.intern("Box");
    const auto sym_Str = compilerContext.identInterner.intern("Str");

    const auto sym_box_new = compilerContext.identInterner.intern("box_new");
    const auto sym_box_free = compilerContext.identInterner.intern("box_free");
    const auto sym_box_len = compilerContext.identInterner.intern("box_len");
    const auto sym_box_get = compilerContext.identInterner.intern("box_get");
    const auto sym_box_set = compilerContext.identInterner.intern("box_set");

    const auto sym_print = compilerContext.identInterner.intern("print");
    const auto sym_put = compilerContext.identInterner.intern("put");
    const auto sym_nl = compilerContext.identInterner.intern("nl");
    const auto main_sym = compilerContext.identInterner.intern("main");

    // ---------------- pipeline ----------------

    const auto pass2 = sema::run_pass2_module_index(translation);
    if (!sema::must_ok_or_stop(std::cerr, "pass2", pass2, compilerContext))
        return 1;

    const auto pass3 = sema::run_pass3_import_resolve(translation, pass2);
    if (!sema::must_ok_or_stop(std::cerr, "pass3", pass3, compilerContext))
        return 1;

    sema::IntrinsicNameIds ids{};
    ids.sym_Box = sym_Box;
    ids.sym_Str = sym_Str;
    ids.sym_box_new = sym_box_new;
    ids.sym_box_free = sym_box_free;
    ids.sym_box_len = sym_box_len;
    ids.sym_box_get = sym_box_get;
    ids.sym_box_set = sym_box_set;
    ids.sym_print = sym_print;
    ids.sym_put = sym_put;
    ids.sym_nl = sym_nl;

    const auto pass3_5 = sema::run_pass3_5_reserved_index(reserved_translation, ids);
    if (!sema::must_ok_or_stop(std::cerr, "pass3.5", pass3_5, compilerContext))
        return 1;

    const auto pass4 = sema::run_pass4_global_symbol_index(translation, pass2, pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass4", pass4, compilerContext))
        return 1;

    const auto pass4_5 = sema::run_pass4_5_visible_env(translation, pass2, pass3, pass4, pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass4.5", pass4_5, compilerContext))
        return 1;

    const auto pass5_reserved =
        sema::run_pass5_reserved_type_resolve(reserved_translation, pass3_5, sym_Box, sym_Str);
    if (!sema::must_ok_or_stop(std::cerr, "pass5_reserved", pass5_reserved, compilerContext))
        return 1;

    auto pass5 = sema::run_pass5_type_resolve(
        translation, compilerContext, pass4_5, pass5_reserved, sym_Box, sym_Str);
    if (!sema::must_ok_or_stop(std::cerr, "pass5", pass5, compilerContext))
        return 1;

    const auto pass6 = sema::run_pass6_local_binder(translation, pass4, pass4_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass6", pass6, compilerContext))
        return 1;

    const auto pass7 = sema::run_pass7(translation, compilerContext, pass4, pass5, pass6, &pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass7", pass7, compilerContext))
        return 1;

    const auto pass8 = sema::run_pass8_dyn_tag(translation, pass4_5, pass6);
    if (!sema::must_ok_or_stop(std::cerr, "pass8", pass8, compilerContext))
        return 1;

    auto pass9_1 = sema::run_pass9_1_bootstrap(translation, "kl_rt");

    auto rt = sema::run_pass9_2_declare_runtime(pass9_1);

    const auto pass9_3 = sema::run_pass9_3_declare_user_and_load_fns(
        pass9_1, pass2, pass4, pass5, compilerContext, main_sym);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.3", pass9_3, compilerContext))
        return 1;

    const auto pass9_5 = sema::run_pass9_5_emit_bodies(
        pass9_1, translation, pass4, pass4_5, pass5, pass6, pass7, pass8, rt);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.5", pass9_5, compilerContext))
        return 1;

    const auto pass9_6 = sema::run_pass9_6_prepare(pass9_1);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.6", pass9_6, compilerContext))
        return 1;

    const auto pass9_7 = sema::run_pass9_7_rt_ops(pass9_1);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.7", pass9_7, compilerContext))
        return 1;

    const auto pass11 = sema::run_pass11_verify_llvm_ir(pass9_1, compilerContext);
    if (!sema::must_ok_or_stop(std::cerr, "pass11", pass11, compilerContext))
        return 1;

    if (has_flag(driverFlags, DriverFlag::DumpIr))
    {
        sema::dump_llvm_ir(std::cout, pass9_1);
    }

    const auto pass12 = sema::run_pass12_execute(
        pass9_1,
        compilerContext,
        /*entry_symbol=*/"main",
        libs,
        /*make_wrapper_if_needed=*/false,
        /*wrapper_name=*/"__kl_entry");

    if (!sema::must_ok_or_stop(std::cerr, "pass12", pass12, compilerContext))
        return 1;

    return 0;
}
