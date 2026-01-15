// sema/pass11.cpp
#include "pass11.hpp"

#include <string>
#include <string_view>
#include <vector>

#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#include "module/module.hpp" // ast::Module (for pathExpr_->path_)

namespace sema
{
    // ------------------------------
    // Helpers: sanitize LLVM messages
    // ------------------------------
    static std::string squash_ws(std::string s, std::size_t max_len = 2000)
    {
        for (char& c : s)
        {
            if (c == '\n' || c == '\r' || c == '\t')
                c = ' ';
        }

        std::string out;
        out.reserve(s.size());
        bool prev_space = false;
        for (char c : s)
        {
            const bool is_space = (c == ' ');
            if (is_space && prev_space) continue;
            out.push_back(c);
            prev_space = is_space;
        }

        if (out.size() > max_len)
        {
            const std::size_t keep = (max_len > 4) ? (max_len - 4) : 0;
            out.resize(keep);
            out += " ...";
        }
        return out;
    }

    // ------------------------------
    // Module-path-first logging
    // ------------------------------
    static const std::vector<lex::SymId>& pass11_module_path(const Pass9_1Result& st)
    {
        static const std::vector<lex::SymId> kEmpty{};

        if (st.log_mod && st.log_mod->pathExpr_)
            return st.log_mod->pathExpr_->path_;

        // Secondary fallback: first unit module, if present.
        for (const ast::Module* m : st.unit_mods)
            if (m && m->pathExpr_)
                return m->pathExpr_->path_;

        return kEmpty;
    }

    static void push_cluster(LogSequence& out,
                             const Pass9_1Result& st,
                             const lex::Loc& loc,
                             std::string message,
                             const LogEntity& cause_entity)
    {
        // 1) REQUIRED: module path first
        out.emplace_back(LogPath{ SymKind::Ident, pass11_module_path(st), loc });

        // 2) message
        out.emplace_back(std::move(message));

        // 3) cause (Log / LogPath)
        out.emplace_back(cause_entity);
    }

    static std::vector<lex::SymId> one_seg_path(CompilerContext& cc, std::string_view s)
    {
        return { cc.identInterner.intern(std::string(s)) };
    }

    Pass11Result run_pass11_verify_llvm_ir(const Pass9_1Result& st, CompilerContext& cc)
    {
        Pass11Result out{};
        const lex::Loc no_loc{};

        if (!st.module)
        {
            const auto cause = LogPath{
                SymKind::String,
                one_seg_path(cc, "<module>"),
                no_loc
            };

            push_cluster(out.errors,
                         st,
                         no_loc,
                         "pass11: internal error: missing LLVM module (Pass9.1 not run?)",
                         cause);
            return out;
        }

        llvm::Module& M = *st.module;

        // 1) Verify each defined function (more local errors)
        for (llvm::Function& F : M)
        {
            if (F.isDeclaration())
                continue;

            std::string raw;
            llvm::raw_string_ostream os(raw);

            const bool broken = llvm::verifyFunction(F, &os);
            os.flush();

            if (!broken)
                continue;

            const std::string fn_name = F.getName().str();
            const lex::SymId fn_sym = cc.identInterner.intern(fn_name);

            std::string msg = raw.empty()
                ? "pass11: LLVM function verification failed"
                : ("pass11: LLVM function verification failed: " + squash_ws(raw));

            const Log cause = Log{ SymKind::Ident, fn_sym, no_loc };

            push_cluster(out.errors, st, no_loc, std::move(msg), cause);
        }

        // 2) Verify whole module (cross-function issues)
        {
            std::string raw;
            llvm::raw_string_ostream os(raw);

            const bool broken = llvm::verifyModule(M, &os);
            os.flush();

            if (broken)
            {
                std::string msg = raw.empty()
                    ? "pass11: LLVM module verification failed"
                    : ("pass11: LLVM module verification failed: " + squash_ws(raw));

                const auto cause = LogPath{
                    SymKind::String,
                    one_seg_path(cc, "<module>"),
                    no_loc
                };

                push_cluster(out.errors, st, no_loc, std::move(msg), cause);
            }
        }

        return out;
    }

} // namespace sema
