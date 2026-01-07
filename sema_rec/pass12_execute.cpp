// sema_rec/pass12_execute.cpp
#include "pass12_execute.hpp"

#include <iostream>

#include "pass9_1_bootstrap.hpp" // for Pass9_1Result

#include <string>
#include <utility>
#include <vector>

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/ExecutionEngine/Orc/Core.h>
#include <llvm/ExecutionEngine/Orc/Mangling.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <llvm/Support/Error.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/raw_ostream.h>

namespace sema
{
    // ------------------------------------------------------------
    // Diagnostics helper
    // ------------------------------------------------------------
    static void push_diag(Pass12Result& out,
                          Pass12Diagnostic::Code c,
                          const lex::Loc& loc,
                          std::string msg)
    {
        out.diagnostics.push_back(Pass12Diagnostic{.code = c, .loc = loc, .message = std::move(msg)});
    }

    static std::string err_to_string(llvm::Error E)
    {
        std::string s;
        llvm::raw_string_ostream os(s);
        os << E;
        return os.str();
    }

    // ------------------------------------------------------------
    // Native init (once)
    // ------------------------------------------------------------
    static void init_native_llvm_once()
    {
        static bool inited = false;
        if (inited) return;
        inited = true;

        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        // Makes current process symbols visible to SearchForAddressOfSymbol.
        llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);
    }

    // ------------------------------------------------------------
    // Wrapper: void @__kl_entry() { call @target(default args); ret void }
    // Default args:
    //   ptr => null, i1 => false, other => undef
    // ------------------------------------------------------------
    static llvm::Function* make_entry_wrapper(llvm::Module& M,
                                              llvm::LLVMContext& C,
                                              llvm::Function& target,
                                              const std::string& wrapper_name)
    {
        if (auto* existing = M.getFunction(wrapper_name))
            return existing;

        auto* voidTy = llvm::Type::getVoidTy(C);
        auto* FT = llvm::FunctionType::get(voidTy, /*isVarArg=*/false);
        auto* F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, wrapper_name, M);

        auto* entryBB = llvm::BasicBlock::Create(C, "entry", F);
        llvm::IRBuilder<> B(entryBB);

        std::vector<llvm::Value*> args;
        args.reserve(target.arg_size());

        for (auto& A : target.args())
        {
            llvm::Type* T = A.getType();

            if (T->isPointerTy())
                args.push_back(llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(T)));
            else if (T->isIntegerTy(1))
                args.push_back(llvm::ConstantInt::getFalse(C));
            else
                args.push_back(llvm::UndefValue::get(T));
        }

        llvm::CallInst* call = B.CreateCall(&target, args);

        // ignore return value intentionally
        (void)call;

        B.CreateRetVoid();
        return F;
    }

    // ------------------------------------------------------------
    // Bind all external declarations in the module to symbols from the current process.
    // This replaces DynamicLibrarySearchGenerator.
    //
    // Notes:
    //  - We bind only functions that are declarations and are not LLVM intrinsics.
    //  - We DO NOT fail immediately if missing; we can optionally diagnose.
    //  - On Linux, your executable often must be linked with -Wl,--export-dynamic
    //    so these symbols are visible for SearchForAddressOfSymbol.
    // ------------------------------------------------------------
    static llvm::Error define_externals_from_current_process(llvm::orc::LLJIT& J,
                                                             llvm::Module& M,
                                                             Pass12Result& out)
    {
        auto& JD = J.getMainJITDylib();
        llvm::orc::MangleAndInterner Mangle(J.getExecutionSession(), J.getDataLayout());

        llvm::orc::SymbolMap symMap;

        // Track missing externals for better diagnostics.
        std::vector<std::string> missing;

        for (auto& F : M)
        {
            if (!F.isDeclaration())
                continue;
            if (F.isIntrinsic())
                continue;

            const std::string name = F.getName().str();

            // Skip LLVM internal namespace if any appear
            if (name.rfind("llvm.", 0) == 0)
                continue;

            void* addr = llvm::sys::DynamicLibrary::SearchForAddressOfSymbol(name);
            if (!addr)
            {
                // Collect. This helps you see exactly what wasn't found.
                missing.push_back(name);
                continue;
            }

            // Exported + callable
            symMap[Mangle(name)] =
                llvm::orc::ExecutorSymbolDef(
                    llvm::orc::ExecutorAddr::fromPtr(addr),
                    llvm::JITSymbolFlags::Exported);
        }

        if (!missing.empty())
        {
            // This is not always fatal (maybe the module never calls that decl),
            // but in your runtime case it IS usually fatal. Diagnose loudly.
            std::string msg = "pass12: host symbols not found for extern decls: ";
            for (size_t i = 0; i < missing.size(); ++i)
            {
                msg += missing[i];
                if (i + 1 < missing.size()) msg += ", ";
            }
            push_diag(out, Pass12Diagnostic::Code::MissingExternalSymbol, lex::Loc{}, std::move(msg));
        }

        if (!symMap.empty())
        {
            if (auto err = JD.define(llvm::orc::absoluteSymbols(std::move(symMap))))
                return err;
        }

        return llvm::Error::success();
    }

    // ------------------------------------------------------------
    // Public pass entry
    // ------------------------------------------------------------
    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    std::string entry_symbol,
                                    bool make_wrapper_if_needed,
                                    std::string wrapper_name)
    {
        Pass12Result out{};
        init_native_llvm_once();

        if (!pass9_1.llctx || !pass9_1.module)
        {
            push_diag(out, Pass12Diagnostic::Code::OwnershipError, lex::Loc{},
                      "pass12: Pass9_1Result.llctx/module are null (already moved or not initialized)");
            return out;
        }

        // Move ownership into pass12 (final stage)
        std::unique_ptr<llvm::LLVMContext> Ctx = std::move(pass9_1.llctx);
        std::unique_ptr<llvm::Module> Mod = std::move(pass9_1.module);

        // Builder references old module/context; drop it.
        pass9_1.builder.reset();
        llvm::errs() << "[pass12] module identifier: " << Mod->getModuleIdentifier() << "\n";
        llvm::errs() << "[pass12] looking for: '" << entry_symbol << "'\n";
        llvm::errs() << "[pass12] functions:\n";
        for (auto& F : Mod->functions()) {
            llvm::errs() << "  - " << F.getName()
                         << (F.isDeclaration() ? " (decl)\n" : " (def)\n");
        }

        // Find entry in module
        llvm::Function* entryF = Mod->getFunction(entry_symbol);
        if (!entryF)
        {
            push_diag(out, Pass12Diagnostic::Code::MissingEntrySymbol, lex::Loc{},
                      "pass12: entry function not found in module: " + entry_symbol);
            return out;
        }

        std::string actual_entry = entry_symbol;

        if (make_wrapper_if_needed)
        {
            const bool needs_wrapper =
                entryF->arg_size() != 0 || !entryF->getReturnType()->isVoidTy();

            if (needs_wrapper)
            {
                llvm::Function* wrap = make_entry_wrapper(*Mod, *Ctx, *entryF, wrapper_name);
                actual_entry = wrap->getName().str();
            }
        }

        // Create JIT
        auto JOrErr = llvm::orc::LLJITBuilder().create();
        if (!JOrErr)
        {
            push_diag(out, Pass12Diagnostic::Code::JitCreateFailed, lex::Loc{},
                      "pass12: failed to create LLJIT: " + err_to_string(JOrErr.takeError()));
            return out;
        }
        std::unique_ptr<llvm::orc::LLJIT> J = std::move(*JOrErr);

        // Ensure module datalayout matches JIT
        Mod->setDataLayout(J->getDataLayout());

        // Define externals (rt_* etc.) from current process.
        if (auto err = define_externals_from_current_process(*J, *Mod, out))
        {
            push_diag(out, Pass12Diagnostic::Code::ExternalSymbolDefineFailed, lex::Loc{},
                      "pass12: defining external symbols failed: " + err_to_string(std::move(err)));
            return out;
        }

        // If you consider missing externals fatal, you can stop here:
        if (!out.diagnostics.empty())
        {
            // If you want "best effort", remove this early return.
            return out;
        }

        // Add module to JIT
        llvm::orc::ThreadSafeModule TSM(std::move(Mod), std::move(Ctx));
        if (auto err = J->addIRModule(std::move(TSM)))
        {
            push_diag(out, Pass12Diagnostic::Code::AddModuleFailed, lex::Loc{},
                      "pass12: addIRModule failed: " + err_to_string(std::move(err)));
            return out;
        }

        // Lookup entry
        auto symOrErr = J->lookup(actual_entry);
        if (!symOrErr)
        {
            push_diag(out, Pass12Diagnostic::Code::LookupFailed, lex::Loc{},
                      "pass12: lookup failed for '" + actual_entry + "': " + err_to_string(symOrErr.takeError()));
            return out;
        }

        const auto addr = symOrErr->getValue();
        if (!addr)
        {
            push_diag(out, Pass12Diagnostic::Code::InvokeFailed, lex::Loc{},
                      "pass12: resolved entry address is 0");
            return out;
        }

        // Call as void()
        using EntryFn = void (*)();
        auto* fn = reinterpret_cast<EntryFn>(static_cast<uintptr_t>(addr));
        std::cerr << "[pass12] calling " << actual_entry << "\n";
        fn();
        std::cerr << "[pass12] returned from " << actual_entry << "\n";

        return out;
    }

} // namespace sema
