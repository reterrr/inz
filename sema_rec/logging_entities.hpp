#ifndef INZ_LOG_HPP
#define INZ_LOG_HPP

#include "sym_kind.hpp"
#include "token.hpp"

#include <string>
#include <variant>
#include <vector>

#include "compiler_context.hpp"

namespace sema
{
    struct Log
    {
        SymKind kind;
        lex::SymId id;
        lex::Loc location;
    };

    struct LogPath
    {
        SymKind kind;
        std::vector<lex::SymId> path;
        lex::Loc location;
    };

    using LogEntity = std::variant<Log, LogPath, std::string>;
    using LogSequence = std::vector<LogEntity>;

    inline void log_msg(LogSequence& out, std::string msg)
    {
        out.emplace_back(std::move(msg));
    }


    inline void log_ident(LogSequence& out, lex::SymId id, const lex::Loc& loc)
    {
        out.emplace_back(Log{SymKind::Ident, id, loc});
    }

    inline void log_string(LogSequence& out, lex::SymId id, const lex::Loc& loc)
    {
        out.emplace_back(Log{SymKind::String, id, loc});
    }

    inline void log_numeric(LogSequence& out, lex::SymId id, const lex::Loc& loc)
    {
        out.emplace_back(Log{SymKind::Numeric, id, loc});
    }


    inline void log_path(LogSequence& out, const std::vector<lex::SymId>& path,
                         const lex::Loc& loc, bool also_log_idents = true)
    {
        out.emplace_back(LogPath{SymKind::Ident, path, loc});
        if (also_log_idents)
        {
            for (lex::SymId s : path)
                out.emplace_back(Log{SymKind::Ident, s, loc});
        }
    }

    static std::string_view sym_to_sv(const CompilerContext& cc, lex::SymId id)
    {
        return cc.identInterner.view(id);
    }

    static std::string sym_id_fallback(lex::SymId id)
    {
        std::ostringstream ss;
        ss << id;

        return ss.str();
    }


    static std::string loc_to_string(const lex::Loc& loc)
    {
        std::ostringstream ss;


        ss << loc;
        return ss.str();
    }

    static void print_path(std::ostream& os,
                           const CompilerContext& cc,
                           const std::vector<lex::SymId>& path)
    {
        for (size_t i = 0; i < path.size(); ++i)
        {
            if (i) os << "::";

            const auto seg = sym_to_sv(cc, path[i]);
            if (!seg.empty())
                os << seg;
            else
                os << "<sym#" << sym_id_fallback(path[i]) << ">";
        }
    }

    static void print_entity_one_line(std::ostream& os,
                                      const CompilerContext& cc,
                                      const LogEntity& e)
    {
        if (std::holds_alternative<std::string>(e))
        {
            os << std::get<std::string>(e);
            return;
        }

        if (std::holds_alternative<Log>(e))
        {
            const Log& l = std::get<Log>(e);
            os << "Ident ";
            const auto nm = sym_to_sv(cc, l.id);
            if (!nm.empty()) os << nm;
            else os << "<sym#" << sym_id_fallback(l.id) << ">";
            os << " @ " << loc_to_string(l.location);
            return;
        }

        const LogPath& p = std::get<LogPath>(e);
        os << "Path ";
        if (!p.path.empty()) print_path(os, cc, p.path);
        else os << "<empty>";
        os << " @ " << loc_to_string(p.location);
    }


    static bool is_module_anchor(const LogEntity& e)
    {
        if (!std::holds_alternative<LogPath>(e)) return false;


        return true;
    }

    static bool is_message(const LogEntity& e)
    {
        return std::holds_alternative<std::string>(e);
    }

    static bool is_cause(const LogEntity& e)
    {
        return std::holds_alternative<Log>(e) || std::holds_alternative<LogPath>(e);
    }

    inline void print_log_sequence(std::ostream& os,
                                   std::string_view pass_name,
                                   const LogSequence& seq,
                                   const CompilerContext& cc)
    {
        if (seq.empty())
            return;

        std::size_t i = 0;
        while (i < seq.size())
        {
            if (i + 2 < seq.size() &&
                is_module_anchor(seq[i]) &&
                is_message(seq[i + 1]) &&
                is_cause(seq[i + 2]))
            {
                const LogPath& mod = std::get<LogPath>(seq[i]);
                const std::string& msg = std::get<std::string>(seq[i + 1]);
                const LogEntity& cause = seq[i + 2];

                os << pass_name << ": " << msg << "\n";

                os << "  module: ";
                if (!mod.path.empty()) print_path(os, cc, mod.path);
                else os << "<unknown-module>";
                os << " @ " << loc_to_string(mod.location) << "\n";

                os << "  cause:  ";
                print_entity_one_line(os, cc, cause);
                os << "\n\n";

                i += 3;
                continue;
            }


            os << pass_name << ": ";
            print_entity_one_line(os, cc, seq[i]);
            os << "\n";
            ++i;
        }
    }
}
#endif
