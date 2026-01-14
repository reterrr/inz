#pragma once

#include <ostream>
#include <string_view>

#include "compiler_context.hpp"
#include "logging_entities.hpp"

namespace sema
{
    template <class T>
    concept HasErrorsSeq = requires(const T& t) { t.errors; };

    template <class T>
    concept HasLogsSeq = requires(const T& t) { t.logs; };

    template <class Result>
    const LogSequence* get_logseq_ptr(const Result& r)
    {
        if constexpr (HasErrorsSeq<Result>) return &r.errors;
        if constexpr (HasLogsSeq<Result>)   return &r.logs;
        return nullptr;
    }

    template <class Result>
    bool must_ok_or_stop(std::ostream& os,
                         std::string_view pass_name,
                         const Result& r,
                         const CompilerContext& cc)
    {
        if (r.ok()) return true;

        const LogSequence* seq = get_logseq_ptr(r);
        if (seq) print_log_sequence(os, pass_name, *seq, cc);
        else os << pass_name << ": failed (no LogSequence member: expected .errors or .logs)\n";

        return false;
    }
} // namespace sema
