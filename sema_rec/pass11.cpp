// sema/pass11.cpp
#include "pass11.hpp"

#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

namespace sema
{
    static void push(Pass11Result& out,
                     Pass11Diagnostic::Code c,
                     std::string subject,
                     std::string msg)
    {
        out.diagnostics.push_back(Pass11Diagnostic{
            .code = c,
            .subject = std::move(subject),
            .message = std::move(msg),
        });
    }

    Pass11Result run_pass11_verify_llvm_ir(const Pass9_1Result& st)
    {
        Pass11Result out{};

        if (!st.module)
        {
            push(out,
                 Pass11Diagnostic::Code::LlvmModuleVerifyFailed,
                 "<module>",
                 "internal error: missing LLVM module (Pass9.1 not run?)");
            return out;
        }

        llvm::Module& M = *st.module;

        // 1) Verify each defined function (helps pinpoint failures)
        for (llvm::Function& F : M)
        {
            if (F.isDeclaration())
                continue;

            std::string msg;
            llvm::raw_string_ostream os(msg);

            const bool broken = llvm::verifyFunction(F, &os);
            os.flush();

            if (broken)
            {
                push(out,
                     Pass11Diagnostic::Code::LlvmFunctionVerifyFailed,
                     F.getName().str(),
                     msg.empty() ? "LLVM function verification failed" : msg);
            }
        }

        // 2) Verify whole module (catches cross-function issues)
        {
            std::string msg;
            llvm::raw_string_ostream os(msg);

            const bool broken = llvm::verifyModule(M, &os);
            os.flush();

            if (broken)
            {
                push(out,
                     Pass11Diagnostic::Code::LlvmModuleVerifyFailed,
                     "<module>",
                     msg.empty() ? "LLVM module verification failed" : msg);
            }
        }

        return out;
    }
} // namespace sema
