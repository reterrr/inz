//
// Created by yhwach on 12/25/25.
//

#ifndef INZ_DUMP_VISITOR_HPP
#define INZ_DUMP_VISITOR_HPP

#include <cstdint>
#include <iosfwd>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <iostream>

#include "core_applying_visit.hpp"
#include "visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"
#include "decls.hpp"
#include "metadata.hpp"

// NOTE: this header uses CompilerContext and lex::SymId.
// Make sure the right headers are included somewhere in your TU.
// #include "compiler_context.hpp"
// #include "lex/sym.hpp"

namespace hir::detail
{
    template <class It>
    inline std::string fmt_path(It& it, const std::vector<lex::SymId>& segs)
    {
        std::string out;
        out.reserve(segs.size() * 10);

        for (size_t i = 0; i < segs.size(); ++i)
        {
            if (i != 0) out += "::";
            out += std::string(it.identInterner_.view(segs[i]));
        }
        return out;
    }

    template <class T>
    inline std::string num(T v)
    {
        std::ostringstream ss;
        ss << static_cast<uint64_t>(v);
        return ss.str();
    }

    template <class T>
    inline std::string opt_num(const std::optional<T>& v)
    {
        if (!v) return "∅";
        return num(*v);
    }

    inline std::string indent(uint32_t d)
    {
        return std::string(d, '\t'); // one tab per depth level
    }

    inline std::string s(std::string_view v) { return std::string(v); }

    inline std::string quoted(std::string_view v)
    {
        std::string out;
        out.reserve(v.size() + 2);
        out.push_back('"');
        out.append(v);
        out.push_back('"');
        return out;
    }

    // ---- MetaData-driven depth + scope (best-effort, compiles even if fields differ) ----

    template <class MD>
    inline uint32_t md_depth(const MD& md)
    {
        if constexpr (requires { md.depth; })
            return static_cast<uint32_t>(md.depth);
        else if constexpr (requires { md.depth(); })
            return static_cast<uint32_t>(md.depth());
        else
            return 0u;
    }

    template <class MD>
    inline std::string md_scope(const MD& md)
    {
        if constexpr (requires { md.scope; })
            return " scope=" + num(md.scope);
        else if constexpr (requires { md.scope_id; })
            return " scope=" + num(md.scope_id);
        else if constexpr (requires { md.scopeId; })
            return " scope=" + num(md.scopeId);
        else
            return {};
    }

    // iterator meta: [kind:index]
    template <class It>
    inline std::string it_meta(const It& it)
    {
        if constexpr (requires { it.kind(); it.index(); })
        {
            std::ostringstream ss;
            ss << " [" << static_cast<size_t>(it.kind()) << ":" << static_cast<uint64_t>(it.index()) << "]";
            return ss.str();
        }
        return {};
    }

    template <class It, class MD>
    inline std::string meta(const It& it, const MD& md)
    {
        std::string out = it_meta(it);
        const std::string sc = md_scope(md);
        if (!sc.empty())
        {
            if (out.empty()) out = " [" + sc.substr(1) + "]"; // keep bracket style if no it_meta
            else out += " {" + sc.substr(1) + "}";
        }
        return out;
    }

    template <class It, class MD>
    inline void line(std::ostream& os, const It& it, const MD& md, const std::string& s)
    {
        os << indent(md_depth(md)) << s << meta(it, md) << '\n';
    }
} // namespace hir::detail


namespace hir
{
    template <typename It>
    struct DumpVisitor final : CoreApplyingVisitor<It, MetaData>
    {
        using Base = CoreApplyingVisitor<It, MetaData>;
        using Base::Base;
        using Base::visit;
        using Base::it_;

        std::ostream& os = std::cout;

        ast::Interner<>& stringInterner_;
        ast::Interner<>& identInterner_;
        ast::Interner<>& numericInterner_;

        DumpVisitor(It& it, CompilerContext& context)
            : Base(it),
              stringInterner_(context.stringInterner),
              identInterner_(context.identInterner),
              numericInterner_(context.numericInterner)
        {
        }

        inline std::string ident(lex::SymId id) { return detail::s(identInterner_.view(id)); }
        inline std::string numlit(lex::SymId id) { return detail::s(numericInterner_.view(id)); }
        inline std::string strlit(lex::SymId id) { return detail::s(stringInterner_.view(id)); }

        // ---- ONLY metadata overrides ----
        void visit(Module&, MetaData) override;
        void visit(Import&, MetaData) override;
        void visit(TypeParam&, MetaData) override;

        void visit(StructFieldDecl&, MetaData) override;
        void visit(StructFieldInit&, MetaData) override;
        void visit(StmtBlock&, MetaData) override;
        void visit(FnDecl&, MetaData) override;
        void visit(StructDecl&, MetaData) override;
        void visit(TypeAliasDecl&, MetaData) override;
        void visit(TypeBuiltin&, MetaData) override;
        void visit(TypePath&, MetaData) override;
        void visit(TypeRef&, MetaData) override;
        void visit(TypeArray&, MetaData) override;
        void visit(ExprPath&, MetaData) override;
        void visit(ExprLitInt&, MetaData) override;
        void visit(ExprLitArray&, MetaData) override;
        void visit(ExprLitFloat&, MetaData) override;
        void visit(ExprLitBool&, MetaData) override;
        void visit(ExprLitChar&, MetaData) override;
        void visit(ExprLitString&, MetaData) override;
        void visit(ExprUnary&, MetaData) override;
        void visit(ExprBinary&, MetaData) override;
        void visit(ExprAssign&, MetaData) override;
        void visit(ExprCall&, MetaData) override;
        void visit(ExprIndex&, MetaData) override;
        void visit(ExprField&, MetaData) override;
        void visit(ExprLitStruct&, MetaData) override;
        void visit(ExprCast&, MetaData) override;
        void visit(Block&, MetaData) override;
        void visit(StmtIf&, MetaData) override;
        void visit(StmtElseIf&, MetaData) override;
        void visit(StmtElse&, MetaData) override;
        void visit(StmtWhile&, MetaData) override;
        void visit(StmtDoWhile&, MetaData) override;
        void visit(StmtBreak&, MetaData) override;
        void visit(StmtContinue&, MetaData) override;
        void visit(StmtReturn&, MetaData) override;
        void visit(StmtVar&, MetaData) override;
        void visit(StmtExpr&, MetaData) override;
        void visit(ParamSelf&, MetaData) override;
        void visit(ParamNamed&, MetaData) override;
        void visit(TraitDecl&, MetaData) override;
        void visit(ImplDecl&, MetaData) override;
        void visit(TraitMethod&, MetaData) override;
        void visit(ImplMethod&, MetaData) override;
    };


    // ------------------ IMPLEMENTATIONS ------------------

    template <typename It>
    void DumpVisitor<It>::visit(Module& m, MetaData md)
    {
        detail::line(os, it_, md, "Module"
                     " package_path=Expr#" + detail::num(m.package_path) +
                     " imports=" + detail::num(m.imports.size()) +
                     " decls=" + detail::num(m.decls.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(Import& i, MetaData md)
    {
        const std::string alias = i.alias ? ident(*i.alias) : std::string("∅");

        detail::line(os, it_, md, "Import"
                     " path=Expr#" + detail::num(i.path) +
                     " alias=" + alias);
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeParam& tp, MetaData md)
    {
        detail::line(os, it_, md, "TypeParam"
                     " name=" + ident(tp.name));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructFieldDecl& f, MetaData md)
    {
        detail::line(os, it_, md, "StructFieldDecl"
                     " name=" + ident(f.name) +
                     " type=Type#" + detail::num(f.type) +
                     " vis=" + detail::num(static_cast<uint32_t>(f.vis)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructFieldInit& f, MetaData md)
    {
        detail::line(os, it_, md, "StructFieldInit"
                     " name=" + ident(f.name) +
                     " value=Expr#" + detail::num(f.value));
    }

    template <typename It>
    void DumpVisitor<It>::visit(Block& b, MetaData md)
    {
        detail::line(os, it_, md, "Block"
                     " stmts=" + detail::num(b.stmts.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(FnDecl& fn, MetaData md)
    {
        detail::line(os, it_, md, "FnDecl"
                     " name=" + ident(fn.header.name) +
                     " exported=" + std::string(fn.exported ? "true" : "false") +
                     " tparams=" + detail::num(fn.tparams.size()) +
                     " params=" + detail::num(fn.header.params.size()) +
                     (fn.header.return_type.has_value()
                          ? " return=Type#" + detail::num(fn.header.return_type.value())
                          : "") +
                     " body=Block#" + detail::num(fn.body));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructDecl& st, MetaData md)
    {
        detail::line(os, it_, md, "StructDecl"
                     " name=" + ident(st.name) +
                     " exported=" + std::string(st.exported ? "true" : "false") +
                     " tparams=" + detail::num(st.tparams.size()) +
                     " fields=" + detail::num(st.fields.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeAliasDecl& ta, MetaData md)
    {
        detail::line(os, it_, md, "TypeAliasDecl"
                     " aliased=Type#" + detail::num(ta.aliased));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeBuiltin& tb, MetaData md)
    {
        detail::line(os, it_, md, "TypeBuiltin"
                     " kind=" + detail::num(static_cast<uint32_t>(tb.kind)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypePath& tp, MetaData md)
    {
        detail::line(os, it_, md, "TypePath"
                     " path=Expr#" + detail::num(tp.path) +
                     " targs=" + detail::num(tp.targs.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeRef& tr, MetaData md)
    {
        detail::line(os, it_, md, "TypeRef"
                     " mut=" + detail::num(static_cast<uint32_t>(tr.mut)) +
                     " inner=Type#" + detail::num(tr.inner));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeArray& ta, MetaData md)
    {
        detail::line(os, it_, md, "TypeArray"
                     " elem=Type#" + detail::num(ta.elem) +
                     " size=Expr#" + detail::num(ta.size));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprPath& ep, MetaData md)
    {
        const auto pid = static_cast<size_t>(ep.path);
        const auto& pe = it_.a.paths.at(pid);
        const auto path_text = detail::fmt_path(*this, pe.path);

        detail::line(os, it_, md, "ExprPath"
                     " path=Path#" + detail::num(ep.path) +
                     " text=" + path_text);
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitInt& li, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitInt"
                     " value=" + numlit(li.sym) +
                     " suffix=" + (li.kind ? detail::num(static_cast<uint32_t>(*li.kind)) : std::string("∅")));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitArray& ea, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitArray"
                     " elements=" + detail::num(ea.elements.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitFloat& lf, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitFloat"
                     " value=" + numlit(lf.sym) +
                     " suffix=" + (lf.kind ? detail::num(static_cast<uint32_t>(*lf.kind)) : std::string("∅")));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitBool& lb, MetaData md)
    {
        detail::line(os, it_, md, std::string("ExprLitBool value=") + (lb.value ? "true" : "false"));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitChar& lc, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitChar"
                     " value=" + detail::num(static_cast<uint32_t>(lc.value)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitString& ls, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitString"
                     " value=" + detail::quoted(strlit(ls.sym)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprUnary& eu, MetaData md)
    {
        detail::line(os, it_, md, "ExprUnary"
                     " op=" + detail::num(static_cast<uint32_t>(eu.op)) +
                     " rhs=Expr#" + detail::num(eu.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprBinary& eb, MetaData md)
    {
        detail::line(os, it_, md, "ExprBinary"
                     " op=" + detail::num(static_cast<uint32_t>(eb.op)) +
                     " lhs=Expr#" + detail::num(eb.lhs) +
                     " rhs=Expr#" + detail::num(eb.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprAssign& ea, MetaData md)
    {
        detail::line(os, it_, md, "ExprAssign"
                     " op=" + detail::num(static_cast<uint32_t>(ea.op)) +
                     " lhs=Expr#" + detail::num(ea.lhs) +
                     " rhs=Expr#" + detail::num(ea.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprCall& ec, MetaData md)
    {
        detail::line(os, it_, md, "ExprCall"
                     " callee=Expr#" + detail::num(ec.callee) +
                     " targs=" + detail::num(ec.targs.size()) +
                     " args=" + detail::num(ec.args.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprIndex& ei, MetaData md)
    {
        detail::line(os, it_, md, "ExprIndex"
                     " base=Expr#" + detail::num(ei.base) +
                     " index=Expr#" + detail::num(ei.index));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprField& ef, MetaData md)
    {
        detail::line(os, it_, md, "ExprField"
                     " base=Expr#" + detail::num(ef.base) +
                     " field=" + ident(ef.field));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitStruct& es, MetaData md)
    {
        detail::line(os, it_, md, "ExprLitStruct"
                     " type=Expr#" + detail::num(es.type) +
                     " fields=" + detail::num(es.fields.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprCast& ec, MetaData md)
    {
        detail::line(os, it_, md, "ExprCast"
                     " expr=Expr#" + detail::num(ec.expr) +
                     " type=Type#" + detail::num(ec.type));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtBlock& sb, MetaData md)
    {
        detail::line(os, it_, md, "StmtBlock"
                     " block=Block#" + detail::num(sb.block) +
                     " kind=" + detail::num(static_cast<uint32_t>(sb.kind)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtIf& si, MetaData md)
    {
        detail::line(os, it_, md, "StmtIf"
                     " cond=Expr#" + detail::num(si.cond) +
                     " then=Block#" + detail::num(si.then_blk) +
                     " elseifs=" + detail::num(si.elseifs.size()) +
                     " else=Stmt#" + detail::opt_num(si.else_));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtElseIf& se, MetaData md)
    {
        detail::line(os, it_, md, "StmtElseIf"
                     " cond=Expr#" + detail::num(se.cond) +
                     " blk=Block#" + detail::num(se.blk));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtElse& se, MetaData md)
    {
        detail::line(os, it_, md, "StmtElse"
                     " blk=Block#" + detail::num(se.blk));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtWhile& sw, MetaData md)
    {
        detail::line(os, it_, md, "StmtWhile"
                     " cond=Expr#" + detail::num(sw.cond) +
                     " body=Block#" + detail::num(sw.body));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtDoWhile& sd, MetaData md)
    {
        detail::line(os, it_, md, "StmtDoWhile"
                     " body=Block#" + detail::num(sd.body) +
                     " cond=Expr#" + detail::num(sd.cond));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtBreak&, MetaData md)
    {
        detail::line(os, it_, md, "StmtBreak");
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtContinue&, MetaData md)
    {
        detail::line(os, it_, md, "StmtContinue");
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtReturn& sr, MetaData md)
    {
        detail::line(os, it_, md, "StmtReturn"
                     " value=Expr#" + detail::opt_num(sr.value));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtVar& sv, MetaData md)
    {
        detail::line(os, it_, md, "StmtVar"
                     " name=" + ident(sv.name) +
                     " mut=" + detail::num(static_cast<uint32_t>(sv.mut)) +
                     " storage=" + detail::num(static_cast<uint32_t>(sv.storage)) +
                     " type=Type#" + detail::num(sv.type) +
                     " init=Expr#" + detail::opt_num(sv.init));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtExpr& se, MetaData md)
    {
        detail::line(os, it_, md, "StmtExpr"
                     " expr=Expr#" + detail::num(se.expr));
    }

    static const char* to_string(ast::SelfParamKind k)
    {
        using K = ast::SelfParamKind;
        switch (k)
        {
        case K::Value: return "self";
        case K::Ref: return "&self";
        case K::RefMut: return "&mut self";
        default: return "self(?)";
        }
    }

    template <typename It>
    void DumpVisitor<It>::visit(ParamSelf& p, MetaData md)
    {
        detail::line(os, it_, md, std::string("ParamSelf kind=") + to_string(p.kind));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ParamNamed& p, MetaData md)
    {
        detail::line(os, it_, md, "ParamNamed"
                     " name=" + ident(p.name) +
                     " type=Type#" + detail::num(p.type));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TraitDecl& t, MetaData md)
    {
        detail::line(os, it_, md, "TraitDecl"
                     " name=" + ident(t.name) +
                     " exported=" + std::string(t.exported ? "true" : "false") +
                     " tparams=" + detail::num(t.tparams.size()) +
                     " methods=" + detail::num(t.methods.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ImplDecl& i, MetaData md)
    {
        detail::line(os, it_, md, "ImplDecl"
                     " trait_path=Expr#" + detail::opt_num(i.trait_path) +
                     " for_type=Type#" + detail::num(i.for_type) +
                     " tparams=" + detail::num(i.tparams.size()) +
                     " methods=" + detail::num(i.methods.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TraitMethod&, MetaData)
    {
    }

    template <typename It>
    void DumpVisitor<It>::visit(ImplMethod&, MetaData)
    {
    }
}


#endif //INZ_DUMP_VISITOR_HPP
