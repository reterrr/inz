#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "sema_rec/pipeline_gate.hpp"
#include "sema_rec/diag_print.hpp"

// your pass includes...
#include "compilation_contoller.hpp"
#include "compiler_context.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "reserved/parser.hpp"
#include "sema_rec/pass2.hpp"
#include "sema_rec/pass3.hpp"
#include "sema_rec/pass_3.5.hpp"
#include "sema_rec/pass4.hpp"
#include "sema_rec/pass_4.5.hpp"
#include "sema_rec/pass5_reserved.hpp"
#include "sema_rec/pass5.hpp"
#include "sema_rec/pass6.hpp"
#include "sema_rec/pass7.hpp"
#include "sema_rec/pass8.hpp"
#include "sema_rec/pass9_1_bootstrap.hpp"
#include "sema_rec/pass9_2_declare_user_fns.hpp"
#include "sema_rec/pass9_3_declare_load_fns.hpp"
#include "sema_rec/pass9_4.hpp"
#include "sema_rec/pass9_5_codegen_bodies.hpp"
#include "sema_rec/pass9_6_literals.hpp"
#include "sema_rec/pass9_7_ops.hpp"
#include "sema_rec/pass11.hpp"
#include "sema_rec/pass12_execute.hpp"

static void dump_module_ir(const sema::Pass9_1Result& st)
{
    if (!st.module) return;
    st.module->print(llvm::errs(), nullptr);
}

int main()
{
    CompilerContext compilerContext;
    CompilationController controller;

    std::string err;
    controller.loadConfiguration("./validate.toml", err);

    const auto config = controller.config;
    const auto dirPath = config.files.filesDir;

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

    // ---------------- parse reserved builtins ----------------
    static constexpr auto kReservedSrc = R"(
        package builtin;

        struct Box<T>;
        struct Str;

        fn box_new<T>(count: i64) -> Box::<T>;
        fn box_free<T>(b: &Box::<T>) -> void;
        fn box_len<T>(b: &Box::<T>) -> i64;
        fn box_get<T>(b: &mut Box::<T>, i: i64) -> T;
        fn box_set<T>(b: &mut Box::<T>, i: i64, v: T) -> void;


        fn print<T>(t: &T) -> void;
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

    // ---------------- loc formatting ----------------
    const sema::LocToStringFn loc_to_string = [&](const lex::Loc& L) -> std::string
    {
        // ADAPT: your real location formatting. For now:
        // If Loc carries file/line/col, use them here.
        (void)L;
        return "<loc>";
    };

    const auto sym_Box = compilerContext.identInterner.intern("Box");
    const auto sym_Str = compilerContext.identInterner.intern("Str");

    const auto sym_box_new = compilerContext.identInterner.intern("box_new");
    const auto sym_box_free = compilerContext.identInterner.intern("box_free");
    const auto sym_box_len = compilerContext.identInterner.intern("box_len");
    const auto sym_box_get = compilerContext.identInterner.intern("box_get");
    const auto sym_box_set = compilerContext.identInterner.intern("box_set");
    const auto main_sym = compilerContext.identInterner.intern("main");

    const auto sym_print = compilerContext.identInterner.intern("print");

    // ---------------- pipeline ----------------

    const auto pass2 = sema::run_pass2_module_index(translation);
    if (!sema::must_ok_or_stop(std::cerr, "pass2", pass2, [&]
    {
        sema::print_diag_list(std::cerr, "pass2", pass2.diagnostics, loc_to_string,
                              [](sema::Pass2Diagnostic::Code) { return std::string_view{"Pass2"}; });
    }))
        return 1;

    const auto pass3 = sema::run_pass3_import_resolve(translation, pass2);
    if (!sema::must_ok_or_stop(std::cerr, "pass3", pass3, [&]
    {
        sema::print_diag_list(std::cerr, "pass3", pass3.diagnostics, loc_to_string,
                              [](sema::Pass3Diagnostic::Code) { return std::string_view{"Pass3"}; });
    }))
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

    const auto pass3_5 = sema::run_pass3_5_reserved_index(reserved_translation, ids);
    if (!sema::must_ok_or_stop(std::cerr, "pass3.5", pass3_5, [&]
    {
        sema::print_diag_list(std::cerr, "pass3.5", pass3_5.diagnostics, loc_to_string,
                              [](sema::Pass3_5Diagnostic::Code c) { return sema::p3_5_code(c); });
    }))
        return 1;

    const auto pass4 = sema::run_pass4_global_symbol_index(translation, pass2, pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass4", pass4, [&]
    {
        sema::print_diag_list(std::cerr, "pass4", pass4.diagnostics, loc_to_string,
                              [](sema::Pass4Diagnostic::Code) { return std::string_view{"Pass4"}; });
    }))
        return 1;

    const auto pass4_5 = sema::run_pass4_5_visible_env(pass2, pass3, pass4, pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass4.5", pass4_5, [&]
    {
        sema::print_diag_list(std::cerr, "pass4.5", pass4_5.diagnostics, loc_to_string,
                              [](sema::Pass4_5Diagnostic::Code c) { return sema::p4_5_code(c); });
    }))
        return 1;


    const auto pass5_reserved = sema::run_pass5_reserved_type_resolve(reserved_translation, pass3_5, sym_Box, sym_Str);
    if (!sema::must_ok_or_stop(std::cerr, "pass5_reserved", pass5_reserved, [&]
    {
        sema::print_diag_list(std::cerr, "pass5_reserved", pass5_reserved.diagnostics, loc_to_string,
                              [](sema::Pass5ReservedDiagnostic::Code c) { return sema::p5r_code(c); });
    }))
        return 1;

    auto pass5 = sema::run_pass5_type_resolve(translation, compilerContext, pass4_5, pass5_reserved, sym_Box, sym_Str);
    if (!sema::must_ok_or_stop(std::cerr, "pass5", pass5, [&]
    {
        sema::print_diag_list(std::cerr, "pass5", pass5.diagnostics, loc_to_string,
                              [](sema::Pass5Diagnostic::Code c) { return sema::p5_code(c); });
    }))
        return 1;


    const auto pass6 = sema::run_pass6_local_binder(translation, pass4, pass4_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass6", pass6, [&]
    {
        sema::print_diag_list(std::cerr, "pass6", pass6.diagnostics, loc_to_string,
                              [](sema::Pass6Diagnostic::Code c) { return sema::p6_code(c); });
    }))
        return 1;

    const auto pass7 = sema::run_pass7(translation, compilerContext, pass4, pass5, pass6, &pass3_5);
    if (!sema::must_ok_or_stop(std::cerr, "pass7", pass7, [&]
    {
        sema::print_diag_list(std::cerr, "pass7", pass7.diagnostics, loc_to_string,
                              [](sema::Pass7Diagnostic::Code) { return std::string_view{"Pass7"}; });
    }))
        return 1;

    const auto pass8 = sema::run_pass8_dyn_tag(translation, pass4_5, pass6);
    if (!sema::must_ok_or_stop(std::cerr, "pass8", pass8, [&]
    {
        sema::print_diag_list(std::cerr, "pass8", pass8.diagnostics, loc_to_string,
                              [](sema::Pass8Diagnostic::Code c) { return sema::p8_code(c); });
    }))
        return 1;

    auto pass9_1 = sema::run_pass9_1_bootstrap(translation, "kl_rt");

    // pass9_2 uses compilerContext directly (recommended signature change)
    auto rt = sema::run_pass9_2_declare_runtime(pass9_1);

    auto pass9_3 = sema::run_pass9_3_declare_user_and_load_fns(pass9_1, pass2, pass4, pass5, compilerContext, main_sym);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.3", pass9_3, [&]
    {
        sema::print_diag_list(std::cerr, "pass9.3", pass9_3.diagnostics, loc_to_string,
                              [](sema::Pass9_3Diagnostic::Code) { return std::string_view{"Pass9_3"}; });
    }))
        return 1;

    // const auto pass9_4 = sema::run_pass9_4_plan_function_frames(translation, pass4, pass6, pass9_1, pass9_3);
    // if (!sema::must_ok_or_stop(std::cerr, "pass9.4", pass9_4, [&]
    // {
    //     sema::print_diag_list(std::cerr, "pass9.4", pass9_4.diagnostics, loc_to_string,
    //                           [](sema::Pass9_4Diagnostic::Code) { return std::string_view{"Pass9_4"}; });
    // }))
    //     return 1;

    const auto pass9_5 = sema::run_pass9_5_emit_bodies(
        pass9_1,
        translation,
        pass4,
        pass4_5,
        pass5,
        pass6,
        pass7,
        pass8,
        rt // RECOMMEND: change signature similarly to accept CompilerContext&
    );

    if (!sema::must_ok_or_stop(std::cerr, "pass9.5", pass9_5, [&]
    {
        sema::print_diag_list(std::cerr, "pass9.5", pass9_5.diagnostics, loc_to_string,
                              [](sema::Pass9_5Diagnostic::Code c) { return sema::p9_5_code(c); });
    }))
        return 1;

    const auto pass9_6 = sema::run_pass9_6_prepare(pass9_1);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.6", pass9_6, [&]
    {
        sema::print_diag_list(std::cerr, "pass9.6", pass9_6.diagnostics, loc_to_string,
                              [](sema::Pass9_6Diagnostic::Code) { return std::string_view{"Pass9_6"}; });
    }))
        return 1;

    const auto pass9_7 = sema::run_pass9_7_rt_ops(pass9_1);
    if (!sema::must_ok_or_stop(std::cerr, "pass9.7", pass9_7, [&]
    {
        sema::print_diag_list(std::cerr, "pass9.7", pass9_7.diagnostics, loc_to_string,
                              [](sema::Pass9_7Diagnostic::Code) { return std::string_view{"Pass9_7"}; });
    }))
        return 1;

    const auto pass11 = sema::run_pass11_verify_llvm_ir(pass9_1);
    if (!pass11.ok())
    {
        sema::print_pass11(std::cerr, pass11);
        std::cerr << "Compilation stopped: pass11 failed.\n";
        return 1;
    }

    dump_module_ir(pass9_1);

    const auto pass12 = sema::run_pass12_execute(
        pass9_1,
        /*entry_symbol=*/"main", // your chosen entry
        /*make_wrapper_if_needed=*/false,
        /*wrapper_name=*/"__kl_entry"
    );

    return 0;
}
