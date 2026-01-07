//
// Created by yhwach on 1/2/26.
//// sema/diag_print.cpp
#include "diag_print.hpp"

// include your pass headers so the enums are visible
#include "pass11.hpp"
#include "sema_rec/pass_3.5.hpp"
#include "sema_rec/pass_4.5.hpp"
#include "sema_rec/pass5_reserved.hpp"
#include "sema_rec/pass5.hpp"
#include "sema_rec/pass6.hpp"
#include "sema_rec/pass8.hpp"
#include "sema_rec/pass9_5_codegen_bodies.hpp"

namespace sema
{
    std::string_view p3_5_code(Pass3_5Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass3_5Diagnostic::Code::DuplicateReservedValueName: return "DuplicateReservedValueName";
        case Pass3_5Diagnostic::Code::DuplicateReservedTypeName:  return "DuplicateReservedTypeName";
        default: return "Pass3_5";
        }
    }

    std::string_view p4_5_code(Pass4_5Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass4_5Diagnostic::Code::ImportAliasCollidesWithLocal:   return "ImportAliasCollidesWithLocal";
        case Pass4_5Diagnostic::Code::ImportedTypeCollidesWithLocal:  return "ImportedTypeCollidesWithLocal";
        case Pass4_5Diagnostic::Code::ImportedValueCollidesWithLocal: return "ImportedValueCollidesWithLocal";
        case Pass4_5Diagnostic::Code::DuplicateImportedTypeName:      return "DuplicateImportedTypeName";
        case Pass4_5Diagnostic::Code::DuplicateImportedValueName:     return "DuplicateImportedValueName";
        default: return "Pass4_5";
        }
    }

    std::string_view p5r_code(Pass5ReservedDiagnostic::Code c)
    {
        switch (c)
        {
        case Pass5ReservedDiagnostic::Code::UnknownTypeName:           return "UnknownTypeName";
        case Pass5ReservedDiagnostic::Code::IllegalBoxArity:           return "IllegalBoxArity";
        case Pass5ReservedDiagnostic::Code::IllegalFixedArrayLength:   return "IllegalFixedArrayLength";
        case Pass5ReservedDiagnostic::Code::UnsupportedTypePathDepth:  return "UnsupportedTypePathDepth";
        case Pass5ReservedDiagnostic::Code::UnsupportedTypeForm:       return "UnsupportedTypeForm";
        default: return "Pass5Reserved";
        }
    }

    std::string_view p5_code(Pass5Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass5Diagnostic::Code::UnknownTypeName:           return "UnknownTypeName";
        case Pass5Diagnostic::Code::UnknownImportAlias:        return "UnknownImportAlias";
        case Pass5Diagnostic::Code::IllegalBoxArity:           return "IllegalBoxArity";
        case Pass5Diagnostic::Code::IllegalFixedArrayLength:   return "IllegalFixedArrayLength";
        case Pass5Diagnostic::Code::UnsupportedTypePathDepth:  return "UnsupportedTypePathDepth";
        case Pass5Diagnostic::Code::UnsupportedTypeForm:       return "UnsupportedTypeForm";
        default: return "Pass5";
        }
    }

    std::string_view p6_code(Pass6Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass6Diagnostic::Code::DuplicateLocalNameInScope: return "DuplicateLocalNameInScope";
        case Pass6Diagnostic::Code::UnresolvedName:            return "UnresolvedName";
        default: return "Pass6";
        }
    }

    std::string_view p8_code(Pass8Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass8Diagnostic::Code::NonBoolCondition:             return "NonBoolCondition";
        case Pass8Diagnostic::Code::UnknownStructInStructLiteral: return "UnknownStructInStructLiteral";
        case Pass8Diagnostic::Code::UnsupportedStructLiteralHead: return "UnsupportedStructLiteralHead";
        default: return "Pass8";
        }
    }

    std::string_view p9_5_code(Pass9_5Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass9_5Diagnostic::Code::MissingBindingsForFn: return "MissingBindingsForFn";
        case Pass9_5Diagnostic::Code::MissingRefBinding:    return "MissingRefBinding";
        case Pass9_5Diagnostic::Code::InvalidCallCallee:    return "InvalidCallCallee";
        case Pass9_5Diagnostic::Code::MissingFnDeclInIR:    return "MissingFnDeclInIR";
        case Pass9_5Diagnostic::Code::MissingFnBody:        return "MissingFnBody";
        case Pass9_5Diagnostic::Code::UnsupportedExpr:      return "UnsupportedExpr";
        case Pass9_5Diagnostic::Code::UnsupportedStmt:      return "UnsupportedStmt";
        default: return "Pass9_5";
        }
    }

    std::string_view p11_code(Pass11Diagnostic::Code c)
    {
        switch (c)
        {
        case Pass11Diagnostic::Code::LlvmFunctionVerifyFailed: return "LlvmFunctionVerifyFailed";
        case Pass11Diagnostic::Code::LlvmModuleVerifyFailed:   return "LlvmModuleVerifyFailed";
        default: return "Pass11";
        }
    }

    void print_pass11(std::ostream& os, const sema::Pass11Result& p11)
    {
        if (p11.diagnostics.empty())
            return;

        os << "[pass11] " << p11.diagnostics.size() << " diagnostic(s)\n";

        for (const auto& d : p11.diagnostics)
        {
            os << "<llvm>: error [pass11:" << p11_code(d.code) << "]";
            if (!d.subject.empty() && d.subject != "<module>")
                os << " in " << d.subject;
            os << ": " << d.message << "\n";
        }
    }
} // namespace sema
