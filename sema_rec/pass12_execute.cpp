// pass12_execute.cpp
#include "pass12_execute.hpp"

#include "pass9_1_bootstrap.hpp" // Pass9_1Result

#include <string>
#include <string_view>
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

namespace sema
{
    // ============================================================
    // Logging helpers: module first, then message, then cause
    // ============================================================

    static std::vector<std::string_view> split_sv(std::string_view s, std::string_view delim)
    {
        std::vector<std::string_view> parts;
        while (true)
        {
            const std::size_t pos = s.find(delim);
            if (pos == std::string_view::npos)
            {
                parts.push_back(s);
                break;
            }
            parts.push_back(s.substr(0, pos));
            s.remove_prefix(pos + delim.size());
        }
        return parts;
    }

    static std::vector<lex::SymId> intern_path(CompilerContext& cc, std::string_view s)
    {
        // Best-effort splitting. LLVM module identifiers are often filenames/paths.
        // This yields a LogPath whose segments are stable and readable.
        std::vector<lex::SymId> segs;

        // First split on "::" (language-ish paths)
        for (std::string_view part : split_sv(s, "::"))
        {
            if (part.empty()) continue;

            // Then split on '/' and '\'
            std::string_view cur = part;

            auto emit_piece = [&](std::string_view piece)
            {
                if (!piece.empty())
                    segs.push_back(cc.identInterner.intern(std::string(piece)));
            };

            while (!cur.empty())
            {
                std::size_t pos = cur.find_first_of("/\\");
                if (pos == std::string_view::npos)
                {
                    emit_piece(cur);
                    break;
                }
                emit_piece(cur.substr(0, pos));
                cur.remove_prefix(pos + 1);
            }
        }

        if (segs.empty())
            segs.push_back(cc.identInterner.intern(std::string(s)));

        return segs;
    }

    static std::vector<lex::SymId> module_path_of(const Pass9_1Result& st, CompilerContext& cc)
    {
        if (st.module)
        {
            const std::string id = st.module->getModuleIdentifier();
            if (!id.empty())
                return intern_path(cc, id);

            const std::string name = st.module->getName().str();
            if (!name.empty())
                return intern_path(cc, name);
        }
        return { cc.identInterner.intern("<llvm-module>") };
    }

    static void log_cluster(LogSequence& out,
                            const std::vector<lex::SymId>& module_path,
                            const lex::Loc& loc,
                            std::string msg,
                            LogEntity cause)
    {
        // 1) module
        out.emplace_back(LogPath{
            .kind = SymKind::Ident,
            .path = module_path,
            .location = loc
        });

        // 2) message
        out.emplace_back(std::move(msg));

        // 3) cause
        out.emplace_back(std::move(cause));
    }

    static void log_cause_ident(LogSequence& out,
                               const std::vector<lex::SymId>& module_path,
                               const lex::Loc& loc,
                               std::string msg,
                               CompilerContext& cc,
                               std::string_view ident_name)
    {
        const lex::SymId id = cc.identInterner.intern(std::string(ident_name));
        log_cluster(out, module_path, loc, std::move(msg), Log{ SymKind::Ident, id, loc });
    }

    static void log_cause_path(LogSequence& out,
                              const std::vector<lex::SymId>& module_path,
                              const lex::Loc& loc,
                              std::string msg,
                              CompilerContext& cc,
                              std::string_view path_text,
                              SymKind kind_for_path = SymKind::String)
    {
        log_cluster(out, module_path, loc, std::move(msg),
                    LogPath{ .kind = kind_for_path, .path = intern_path(cc, path_text), .location = loc });
    }

    // ============================================================
    // LLVM helper
    // ============================================================

    static std::string err_to_string(llvm::Error E)
    {
        return llvm::toString(std::move(E));
    }

    static void init_native_llvm_once()
    {
        static bool inited = false;
        if (inited) return;
        inited = true;

        llvm::InitializeNativeTarget();
        llvm::InitializeNativeTargetAsmPrinter();
        llvm::InitializeNativeTargetAsmParser();

        // Makes current process symbols visible to SearchForAddressOfSymbol.
        (void)llvm::sys::DynamicLibrary::LoadLibraryPermanently(nullptr);
    }

    static bool load_shared_library(Pass12Result& out,
                                    CompilerContext& cc,
                                    const std::vector<lex::SymId>& mod_path,
                                    std::string_view path)
    {
        std::string err;
        auto lib = llvm::sys::DynamicLibrary::getPermanentLibrary(std::string(path).c_str(), &err);
        if (!lib.isValid())
        {
            log_cause_path(out.errors,
                           mod_path,
                           lex::Loc{},
                           "pass12: failed to load shared library: " + (err.empty() ? std::string("<no details>") : err),
                           cc,
                           path,
                           SymKind::String);
            return false;
        }
        return true;
    }

    // ============================================================
    // Wrapper: void @__kl_entry() { call @target(default args); ret void }
    // Default args:
    //   ptr => null, i1 => false, other => undef
    // ============================================================

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

        (void)B.CreateCall(&target, args);
        B.CreateRetVoid();
        return F;
    }

    // ============================================================
    // Bind external declarations to current process symbols
    // ============================================================

    static llvm::Error define_externals_from_current_process(llvm::orc::LLJIT& J,
                                                             llvm::Module& M,
                                                             Pass12Result& out,
                                                             CompilerContext& cc,
                                                             const std::vector<lex::SymId>& mod_path)
    {
        auto& JD = J.getMainJITDylib();
        llvm::orc::MangleAndInterner Mangle(J.getExecutionSession(), J.getDataLayout());

        llvm::orc::SymbolMap symMap;

        // Emit one cluster per missing external so the "cause" is a single SymId.
        std::vector<std::string> missing;

        for (auto& F : M)
        {
            if (!F.isDeclaration())
                continue;
            if (F.isIntrinsic())
                continue;

            const std::string name = F.getName().str();
            if (name.rfind("llvm.", 0) == 0)
                continue;

            void* addr = llvm::sys::DynamicLibrary::SearchForAddressOfSymbol(name);
            if (!addr)
            {
                missing.push_back(name);
                continue;
            }

            symMap[Mangle(name)] =
                llvm::orc::ExecutorSymbolDef(
                    llvm::orc::ExecutorAddr::fromPtr(addr),
                    llvm::JITSymbolFlags::Exported);
        }

        for (const std::string& nm : missing)
        {
            log_cause_ident(out.errors,
                            mod_path,
                            lex::Loc{},
                            "pass12: host symbol not found for extern declaration",
                            cc,
                            nm);
        }

        if (!symMap.empty())
        {
            if (auto err = JD.define(llvm::orc::absoluteSymbols(std::move(symMap))))
                return err;
        }

        return llvm::Error::success();
    }

    // ============================================================
    // Internal implementation
    // ============================================================

    static Pass12Result run_pass12_execute_impl(Pass9_1Result& pass9_1,
                                               CompilerContext& cc,
                                               std::string entry_symbol,
                                               const std::vector<std::string>& shared_libs,
                                               bool make_wrapper_if_needed,
                                               std::string wrapper_name)
    {
        Pass12Result out{};
        init_native_llvm_once();

        const std::vector<lex::SymId> mod_path = module_path_of(pass9_1, cc);

        if (!pass9_1.llctx || !pass9_1.module)
        {
            log_cause_path(out.errors,
                           mod_path,
                           lex::Loc{},
                           "pass12: Pass9_1Result.llctx/module are null (already moved or not initialized)",
                           cc,
                           "Pass9_1Result",
                           SymKind::Ident);
            return out;
        }

        // Move ownership into pass12
        std::unique_ptr<llvm::LLVMContext> Ctx = std::move(pass9_1.llctx);
        std::unique_ptr<llvm::Module>      Mod = std::move(pass9_1.module);

        // Builder references old module/context; drop it.
        pass9_1.builder.reset();

        // Find entry in module
        llvm::Function* entryF = Mod->getFunction(entry_symbol);
        if (!entryF)
        {
            log_cause_ident(out.errors,
                            mod_path,
                            lex::Loc{},
                            "pass12: entry function not found in module",
                            cc,
                            entry_symbol);
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
            log_cause_path(out.errors,
                           mod_path,
                           lex::Loc{},
                           "pass12: failed to create LLJIT: " + err_to_string(JOrErr.takeError()),
                           cc,
                           "LLJITBuilder::create",
                           SymKind::String);
            return out;
        }
        std::unique_ptr<llvm::orc::LLJIT> J = std::move(*JOrErr);

        // Ensure module datalayout matches JIT
        Mod->setDataLayout(J->getDataLayout());

        // Load requested shared libraries BEFORE resolving extern declarations.
        for (const std::string& libPath : shared_libs)
        {
            if (!load_shared_library(out, cc, mod_path, libPath))
                return out; // already logged
        }

        // Bind extern declarations to symbols from current process (includes loaded libs).
        if (auto err = define_externals_from_current_process(*J, *Mod, out, cc, mod_path))
        {
            log_cause_path(out.errors,
                           mod_path,
                           lex::Loc{},
                           "pass12: defining external symbols failed: " + err_to_string(std::move(err)),
                           cc,
                           "JITDylib::define",
                           SymKind::String);
            return out;
        }

        // Treat missing externs as fatal (matches your existing behavior).
        if (!out.ok())
            return out;

        // Add module to JIT
        llvm::orc::ThreadSafeModule TSM(std::move(Mod), std::move(Ctx));
        if (auto err = J->addIRModule(std::move(TSM)))
        {
            log_cause_path(out.errors,
                           mod_path,
                           lex::Loc{},
                           "pass12: addIRModule failed: " + err_to_string(std::move(err)),
                           cc,
                           "LLJIT::addIRModule",
                           SymKind::String);
            return out;
        }

        // Lookup entry
        auto symOrErr = J->lookup(actual_entry);
        if (!symOrErr)
        {
            log_cause_ident(out.errors,
                            mod_path,
                            lex::Loc{},
                            "pass12: lookup failed: " + err_to_string(symOrErr.takeError()),
                            cc,
                            actual_entry);
            return out;
        }

        const auto addr = symOrErr->getValue();
        if (!addr)
        {
            log_cause_ident(out.errors,
                            mod_path,
                            lex::Loc{},
                            "pass12: resolved entry address is 0",
                            cc,
                            actual_entry);
            return out;
        }

        // Call as void()
        using EntryFn = void (*)();
        auto* fn = reinterpret_cast<EntryFn>(static_cast<std::uintptr_t>(addr));
        fn();

        return out;
    }

    // ============================================================
    // Public API
    // ============================================================

    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    CompilerContext& cc,
                                    std::string entry_symbol,
                                    bool make_wrapper_if_needed,
                                    std::string wrapper_name)
    {
        static constexpr std::vector<std::string> no_libs{};
        return run_pass12_execute_impl(pass9_1, cc, std::move(entry_symbol), no_libs,
                                      make_wrapper_if_needed, std::move(wrapper_name));
    }

    Pass12Result run_pass12_execute(Pass9_1Result& pass9_1,
                                    CompilerContext& cc,
                                    std::string entry_symbol,
                                    const std::vector<std::string>& shared_libs,
                                    bool make_wrapper_if_needed,
                                    std::string wrapper_name)
    {
        return run_pass12_execute_impl(pass9_1, cc, std::move(entry_symbol), shared_libs,
                                      make_wrapper_if_needed, std::move(wrapper_name));
    }

} // namespace sema
