#include "pass_3.5.hpp"

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "expr/path_expr.hpp"

namespace sema
{
    static thread_local std::vector<lex::SymId> g_cur_module_path;

    static inline void log_module_path_first(LogSequence& logs,
                                             const lex::Loc& loc)
    {
        logs.emplace_back(LogPath{SymKind::Ident, g_cur_module_path, loc});
    }


    static std::optional<RuntimeIntrinsic>
    classify_intrinsic(lex::SymId name, const IntrinsicNameIds& ids)
    {
        if (name == ids.sym_box_new)
            return RuntimeIntrinsic::box_new;
        if (name == ids.sym_box_free)
            return RuntimeIntrinsic::box_free;
        if (name == ids.sym_box_len)
            return RuntimeIntrinsic::box_len;
        if (name == ids.sym_box_get)
            return RuntimeIntrinsic::box_get;
        if (name == ids.sym_box_set)
            return RuntimeIntrinsic::box_set;
        if (name == ids.sym_print)
            return RuntimeIntrinsic::print;
        if (name == ids.sym_put)
            return RuntimeIntrinsic::put;
        if (name == ids.sym_nl)
            return RuntimeIntrinsic::nl;
        return std::nullopt;
    }


    void Pass3_5ReservedIndexVisitor::visit(ast::Module& m)
    {
        g_cur_module_path.clear();
        if (m.pathExpr_)
            g_cur_module_path = m.pathExpr_->path_;


        ast::visitor::OverallVisitor::visit(m);


        g_cur_module_path.clear();
    }

    void Pass3_5ReservedIndexVisitor::visit(ast::StructDecl& s)
    {
        const lex::SymId name = s.name_;


        if (!out_.reserved.type.insert(name).second)
        {
            log_module_path_first(out_.logs, s.location_);

            out_.logs.emplace_back(std::string(
                "pass3.5: DuplicateReservedTypeName: duplicate reserved type name: "));
            out_.logs.emplace_back(Log{SymKind::Ident, name, s.location_});
            return;
        }


        ReservedStructFlags flags = ReservedStructFlags::None;


        if (name == ids_.sym_Box)
            flags |= ReservedStructFlags::NoLit;


        out_.sigs.structs.emplace(name, ReservedStruct{.decl = &s, .flags = flags});


        const StructId sid{next_struct_index_++};
        out_.struct_by_name.emplace(name, sid);
    }

    void Pass3_5ReservedIndexVisitor::visit(ast::FnDecl& f)
    {
        const lex::SymId name = f.name_;


        if (!out_.reserved.value.insert(name).second)
        {
            log_module_path_first(out_.logs, f.location_);

            out_.logs.emplace_back(std::string("pass3.5: DuplicateReservedValueName: "
                "duplicate reserved value name: "));
            out_.logs.emplace_back(Log{SymKind::Ident, name, f.location_});
            return;
        }


        out_.sigs.fns.emplace(name, &f);


        const FnId fid{next_fn_index_++};
        out_.fn_by_name.emplace(name, fid);


        if (auto k = classify_intrinsic(name, ids_); k.has_value())
            out_.intrinsic_by_name.emplace(name, *k);
    }


    Pass3_5Result run_pass3_5_reserved_index(const Translation& reserved_tr,
                                             IntrinsicNameIds ids)
    {
        Pass3_5Result out{};


        out.struct_by_name.reserve(32);
        out.fn_by_name.reserve(64);
        out.load_fn_by_name.reserve(16);
        out.intrinsic_by_name.reserve(32);

        out.sigs.structs.reserve(32);
        out.sigs.fns.reserve(64);


        Pass3_5ReservedIndexVisitor vis(out, ids);

        for (const auto& unit : reserved_tr.units)
        {
            if (!unit.module_)
                continue;

            unit.module_->accept(vis);
        }

        return out;
    }
}
