#include "pass_3.5.hpp"

#include <optional>
#include <sstream>
#include <utility>

namespace sema
{
    static std::optional<RuntimeIntrinsic> classify_intrinsic(lex::SymId name,
                                                              const IntrinsicNameIds& ids)
    {
        if (name == ids.sym_box_new)  return RuntimeIntrinsic::box_new;
        if (name == ids.sym_box_free) return RuntimeIntrinsic::box_free;
        if (name == ids.sym_box_len)  return RuntimeIntrinsic::box_len;
        if (name == ids.sym_box_get)  return RuntimeIntrinsic::box_get;
        if (name == ids.sym_box_set)  return RuntimeIntrinsic::box_set;
        if (name == ids.sym_print)    return RuntimeIntrinsic::print;
        return std::nullopt;
    }

    void Pass3_5ReservedIndexVisitor::diag(Pass3_5Diagnostic::Code code,
                                           const lex::Loc& loc,
                                           std::string msg) const
    {
        out_.diagnostics.push_back(Pass3_5Diagnostic{
            .code = code,
            .loc = loc,
            .message = std::move(msg),
        });
    }

    void Pass3_5ReservedIndexVisitor::visit(ast::Module& m)
    {
        // This will visit StructDecl/FnDecl nodes.
        ast::visitor::OverallVisitor::visit(m);
    }

    void Pass3_5ReservedIndexVisitor::visit(ast::StructDecl& s)
    {
        const lex::SymId name = s.name_;

        // Track as reserved type
        if (!out_.reserved.type.insert(name).second)
        {
            std::ostringstream oss;
            oss << "duplicate reserved type name: " << static_cast<std::uint32_t>(name);
            diag(Pass3_5Diagnostic::Code::DuplicateReservedTypeName, s.location_, oss.str());
            return;
        }

        // Assign reserved struct flags
        ReservedStructFlags flags = ReservedStructFlags::None;

        // Policy: Box has no literal syntax (Box{...} forbidden)
        if (name == ids_.sym_Box)
            flags |= ReservedStructFlags::NoLit;

        // Store signature pointer + flags
        out_.sigs.structs.emplace(name, ReservedStruct{ .decl = &s, .flags = flags });

        // Assign stable StructId for this compilation run
        const StructId sid{ next_struct_index_++ };
        out_.struct_by_name.emplace(name, sid);

        // Do NOT recurse into fields/body for reserved index; prototypes only.
        // If you need to scan attributes later, do it explicitly elsewhere.
    }

    void Pass3_5ReservedIndexVisitor::visit(ast::FnDecl& f)
    {
        const lex::SymId name = f.name_;

        // Track as reserved value
        if (!out_.reserved.value.insert(name).second)
        {
            std::ostringstream oss;
            oss << "duplicate reserved value name: " << static_cast<std::uint32_t>(name);
            diag(Pass3_5Diagnostic::Code::DuplicateReservedValueName, f.location_, oss.str());
            return;
        }

        // Store prototype pointer (for later signature-based lowering if desired)
        out_.sigs.fns.emplace(name, &f);

        // Assign stable FnId for this compilation run
        const FnId fid{ next_fn_index_++ };
        out_.fn_by_name.emplace(name, fid);

        // Classify runtime intrinsics (so later passes bind as RuntimeIntrinsic)
        if (auto k = classify_intrinsic(name, ids_); k.has_value())
            out_.intrinsic_by_name.emplace(name, *k);

        // Do NOT recurse into body; reserved prototypes typically have no body.
    }

    Pass3_5Result run_pass3_5_reserved_index(const Translation& reserved_tr, IntrinsicNameIds ids)
    {
        Pass3_5Result out{};

        // Reserve some capacity (tune as you like)
        out.struct_by_name.reserve(32);
        out.fn_by_name.reserve(64);
        out.load_fn_by_name.reserve(16);
        out.intrinsic_by_name.reserve(32);

        out.sigs.structs.reserve(32);
        out.sigs.fns.reserve(64);

        // IMPORTANT: one visitor for all reserved units, so IDs keep incrementing
        Pass3_5ReservedIndexVisitor vis(out, ids);

        for (const auto& unit : reserved_tr.units)
        {
            if (!unit.module_)
                continue;

            unit.module_->accept(vis);
        }

        return out;
    }
} // namespace sema
