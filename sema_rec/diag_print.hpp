// sema/diag_print.hpp
#pragma once

#include <functional>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "pass11.hpp"
#include "pass5.hpp"
#include "pass5_reserved.hpp"
#include "pass6.hpp"
#include "pass8.hpp"
#include "pass9_5_codegen_bodies.hpp"
#include "pass_4.5.hpp"
#include "token.hpp"

namespace sema
{
    using LocToStringFn = std::function<std::string(const lex::Loc&)>;

    // Generic printer for passes whose diagnostic is { code, loc, message }.
    template <class DiagT, class CodeToStringFn>
    void print_diag_list(std::ostream& os,
                         std::string_view pass_name,
                         const std::vector<DiagT>& diags,
                         const LocToStringFn& loc_to_string,
                         CodeToStringFn&& code_to_string)
    {
        if (diags.empty())
            return;

        os << "[" << pass_name << "] " << diags.size() << " diagnostic(s)\n";

        for (const auto& d : diags)
        {
            const std::string loc = loc_to_string ? loc_to_string(d.loc) : std::string("<loc?>");

            os << loc << ": error"
                << " [" << pass_name << ":" << std::string_view(code_to_string(d.code)) << "]"
                << ": " << d.message << "\n";
        }
    }

    // ---------- code -> string helpers (declare) ----------
    // Implement these in diag_print.cpp

    // pass3.5 (you have exact enum)
    std::string_view p3_5_code_name(std::uint8_t code_value); // fallback (optional)

    // If you prefer strongly typed overloads:
    std::string_view p3_5_code(Pass3_5Diagnostic::Code);

    // pass4.5
    std::string_view p4_5_code(Pass4_5Diagnostic::Code);

    // pass5_reserved
    std::string_view p5r_code(Pass5ReservedDiagnostic::Code);

    // pass5
    std::string_view p5_code(Pass5Diagnostic::Code);

    // pass6
    std::string_view p6_code(Pass6Diagnostic::Code);

    // pass8
    std::string_view p8_code(Pass8Diagnostic::Code);

    // pass9.5
    std::string_view p9_5_code(Pass9_5Diagnostic::Code);

    // pass11
    std::string_view p11_code(Pass11Diagnostic::Code);

    // ---------- pass11 printer ----------
    // pass11 diagnostics are not lex-located; they have subject/message.
    // Adjust to your Pass11Result/Diagnostic fields.
    void print_pass11(std::ostream& os, const sema::Pass11Result& p11);
} // namespace sema
