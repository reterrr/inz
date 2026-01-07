// sema/pipeline_gate.hpp
#pragma once

#include <ostream>
#include <string_view>

namespace sema
{
    template <class ResultT, class PrintFn>
    bool must_ok_or_stop(std::ostream& os,
                         std::string_view pass_name,
                         const ResultT& r,
                         PrintFn&& print_one_pass_diags)
    {
        if (r.ok())
            return true;

        // Print only THIS pass diagnostics here.
        print_one_pass_diags();

        os << "Compilation stopped: " << pass_name << " failed.\n";
        return false;
    }
} // namespace sema
