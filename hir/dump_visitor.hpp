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

#include "visitor.hpp"
#include "exprs.hpp"
#include "modules.hpp"
#include "stmts.hpp"
#include "hir_types.hpp"
#include "decls.hpp"

// NOTE: this header uses CompilerContext and lex::SymId.
// Make sure the right headers are included somewhere in your TU.
// #include "compiler_context.hpp"
// #include "lex/sym.hpp"

namespace hir
{
    namespace detail
    {
        template <class It>
        inline std::string fmt_path(It& it, const std::vector<lex::SymId>& segs)
        {
            std::string out;
            // rough reserve: average 8 chars per segment + separators
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

        inline std::string s(std::string_view v)
        {
            return std::string(v);
        }

        inline std::string quoted(std::string_view v)
        {
            std::string out;
            out.reserve(v.size() + 2);
            out.push_back('"');
            out.append(v);
            out.push_back('"');
            return out;
        }

        // best-effort meta; compiles even if iterator doesn't expose these
        template <class It>
        inline uint32_t depth(const It& it)
        {
            if constexpr (requires { it.depth(); })
                return static_cast<uint32_t>(it.depth());
            else
                return 0u;
        }

        template <class It>
        inline std::string meta(const It& it)
        {
            if constexpr (requires { it.kind(); it.index(); })
            {
                std::ostringstream ss;
                ss << " [" << static_cast<size_t>(it.kind()) << ":" << static_cast<uint64_t>(it.index()) << "]";
                return ss.str();
            }
            return {};
        }

        template <class It>
        inline void line(std::ostream& os, const It& it, const std::string& s)
        {
            os << indent(depth(it)) << s << meta(it) << '\n';
        }
    } // namespace detail


    template <typename It>
    struct DumpVisitor final : Visitor<It>
    {
        using Base = Visitor<It>;
        using Base::Visitor;
        using Base::visit;
        using Base::it_;

        std::ostream& os = std::cout;

        ast::Interner<>& stringInterner_;
        ast::Interner<>& identInterner_;
        ast::Interner<>& numericInterner_;

        explicit DumpVisitor(It& it, CompilerContext& context)
            : Base(it),
              stringInterner_(context.stringInterner),
              identInterner_(context.identInterner),
              numericInterner_(context.numericInterner)
        {
        }

        // helpers to keep call sites readable
        inline std::string ident(lex::SymId id) { return detail::s(identInterner_.view(id)); }
        inline std::string numlit(lex::SymId id) { return detail::s(numericInterner_.view(id)); }
        inline std::string strlit(lex::SymId id) { return detail::s(stringInterner_.view(id)); }

        void visit(Module&) override;
        void visit(Import&) override;
        void visit(TypeParam&) override;
        void visit(Param&) override;
        void visit(StructFieldDecl&) override;
        void visit(StructFieldInit&) override;
        void visit(Block&) override;
        void visit(FnDecl&) override;
        void visit(StructDecl&) override;
        void visit(TypeAliasDecl&) override;
        void visit(TypeBuiltin&) override;
        void visit(TypePath&) override;
        void visit(TypeRef&) override;
        void visit(TypeArray&) override;
        void visit(ExprPath&) override;
        void visit(ExprLitInt&) override;
        void visit(ExprLitArray&) override;
        void visit(ExprLitFloat&) override;
        void visit(ExprLitBool&) override;
        void visit(ExprLitChar&) override;
        void visit(ExprLitString&) override;
        void visit(ExprUnary&) override;
        void visit(ExprBinary&) override;
        void visit(ExprAssign&) override;
        void visit(ExprCall&) override;
        void visit(ExprIndex&) override;
        void visit(ExprField&) override;
        void visit(ExprLitStruct&) override;
        void visit(ExprCast&) override;
        void visit(StmtBlock&) override;
        void visit(StmtIf&) override;
        void visit(StmtElseIf&) override;
        void visit(StmtElse&) override;
        void visit(StmtWhile&) override;
        void visit(StmtDoWhile&) override;
        void visit(StmtBreak&) override;
        void visit(StmtContinue&) override;
        void visit(StmtReturn&) override;
        void visit(StmtVar&) override;
        void visit(StmtExpr&) override;
    };

    // ------------------ IMPLEMENTATIONS ------------------

    template <typename It>
    void DumpVisitor<It>::visit(Module& m)
    {
        detail::line(os, it_, "Module"
                     " package_path=Expr#" + detail::num(m.package_path) +
                     " imports=" + detail::num(m.imports.size()) +
                     " decls=" + detail::num(m.decls.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(Import& i)
    {
        // alias: ident interner
        const std::string alias =
            i.alias ? ident(*i.alias) : std::string("∅");

        detail::line(os, it_, "Import"
                     " path=Expr#" + detail::num(i.path) +
                     " alias=" + alias);
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeParam& tp)
    {
        detail::line(os, it_, "TypeParam"
                     " name=" + ident(tp.name));
    }

    template <typename It>
    void DumpVisitor<It>::visit(Param& p)
    {
        detail::line(os, it_, "Param"
                     " name=" + ident(p.name) +
                     " type=Type#" + detail::num(p.type));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructFieldDecl& f)
    {
        detail::line(os, it_, "StructFieldDecl"
                     " name=" + ident(f.name) +
                     " type=Type#" + detail::num(f.type) +
                     " vis=" + detail::num(static_cast<uint32_t>(f.vis)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructFieldInit& f)
    {
        detail::line(os, it_, "StructFieldInit"
                     " name=" + ident(f.name) +
                     " value=Expr#" + detail::num(f.value));
    }

    template <typename It>
    void DumpVisitor<It>::visit(Block& b)
    {
        detail::line(os, it_, "Block"
                     " stmts=" + detail::num(b.stmts.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(FnDecl& fn)
    {
        detail::line(os, it_, "FnDecl"
                     " name=" + ident(fn.name) +
                     " exported=" + std::string(fn.exported ? "true" : "false") +
                     " tparams=" + detail::num(fn.tparams.size()) +
                     " params=" + detail::num(fn.params.size()) +
                     " return=Type#" + detail::num(fn.return_type) +
                     " body=Block#" + detail::opt_num(fn.body));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StructDecl& st)
    {
        detail::line(os, it_, "StructDecl"
                     " name=" + ident(st.name) +
                     " exported=" + std::string(st.exported ? "true" : "false") +
                     " tparams=" + detail::num(st.tparams.size()) +
                     " fields=" + detail::num(st.fields.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeAliasDecl& ta)
    {
        detail::line(os, it_, "TypeAliasDecl"
                     " aliased=Type#" + detail::num(ta.aliased));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeBuiltin& tb)
    {
        detail::line(os, it_, "TypeBuiltin"
                     " kind=" + detail::num(static_cast<uint32_t>(tb.kind)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypePath& tp)
    {
        detail::line(os, it_, "TypePath"
                     " path=Expr#" + detail::num(tp.path) +
                     " targs=" + detail::num(tp.targs.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeRef& tr)
    {
        detail::line(os, it_, "TypeRef"
                     " mut=" + detail::num(static_cast<uint32_t>(tr.mut)) +
                     " inner=Type#" + detail::num(tr.inner));
    }

    template <typename It>
    void DumpVisitor<It>::visit(TypeArray& ta)
    {
        detail::line(os, it_, "TypeArray"
                     " elem=Type#" + detail::num(ta.elem) +
                     " size=Expr#" + detail::num(ta.size));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprPath& ep)
    {
        // If you later want to print the textual path, you can look up it_.a.paths[ep.path]
        const auto pid = static_cast<size_t>(ep.path);
        const auto& pe = it_.a.paths.at(pid);          // use .at for safety in debug
        const auto path_text = detail::fmt_path(*this, pe.path);

        detail::line(os, it_, "ExprPath"
                     " path=Path#" + detail::num(ep.path) +
                     " text=" + path_text);
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitInt& li)
    {
        // sym: numeric interner
        detail::line(os, it_, "ExprLitInt"
                     " value=" + numlit(li.sym) +
                     " suffix=" + (li.kind ? detail::num(static_cast<uint32_t>(*li.kind)) : std::string("∅")));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitArray& ea)
    {
        detail::line(os, it_, "ExprLitArray"
                     " elements=" + detail::num(ea.elements.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitFloat& lf)
    {
        // sym: numeric interner
        detail::line(os, it_, "ExprLitFloat"
                     " value=" + numlit(lf.sym) +
                     " suffix=" + (lf.kind ? detail::num(static_cast<uint32_t>(*lf.kind)) : std::string("∅")));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitBool& lb)
    {
        detail::line(os, it_, std::string("ExprLitBool value=") + (lb.value ? "true" : "false"));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitChar& lc)
    {
        detail::line(os, it_, "ExprLitChar"
                     " value=" + detail::num(static_cast<uint32_t>(lc.value)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitString& ls)
    {
        // sym: string interner
        detail::line(os, it_, "ExprLitString"
                     " value=" + detail::quoted(strlit(ls.sym)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprUnary& eu)
    {
        detail::line(os, it_, "ExprUnary"
                     " op=" + detail::num(static_cast<uint32_t>(eu.op)) +
                     " rhs=Expr#" + detail::num(eu.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprBinary& eb)
    {
        detail::line(os, it_, "ExprBinary"
                     " op=" + detail::num(static_cast<uint32_t>(eb.op)) +
                     " lhs=Expr#" + detail::num(eb.lhs) +
                     " rhs=Expr#" + detail::num(eb.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprAssign& ea)
    {
        detail::line(os, it_, "ExprAssign"
                     " op=" + detail::num(static_cast<uint32_t>(ea.op)) +
                     " lhs=Expr#" + detail::num(ea.lhs) +
                     " rhs=Expr#" + detail::num(ea.rhs));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprCall& ec)
    {
        detail::line(os, it_, "ExprCall"
                     " callee=Expr#" + detail::num(ec.callee) +
                     " targs=" + detail::num(ec.targs.size()) +
                     " args=" + detail::num(ec.args.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprIndex& ei)
    {
        detail::line(os, it_, "ExprIndex"
                     " base=Expr#" + detail::num(ei.base) +
                     " index=Expr#" + detail::num(ei.index));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprField& ef)
    {
        detail::line(os, it_, "ExprField"
                     " base=Expr#" + detail::num(ef.base) +
                     " field=" + ident(ef.field));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprLitStruct& es)
    {
        detail::line(os, it_, "ExprLitStruct"
                     " type=Expr#" + detail::num(es.type) +
                     " fields=" + detail::num(es.fields.size()));
    }

    template <typename It>
    void DumpVisitor<It>::visit(ExprCast& ec)
    {
        detail::line(os, it_, "ExprCast"
                     " expr=Expr#" + detail::num(ec.expr) +
                     " type=Type#" + detail::num(ec.type));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtBlock& sb)
    {
        detail::line(os, it_, "StmtBlock"
                     " block=Block#" + detail::num(sb.block) +
                     " kind=" + detail::num(static_cast<uint32_t>(sb.kind)));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtIf& si)
    {
        detail::line(os, it_, "StmtIf"
                     " cond=Expr#" + detail::num(si.cond) +
                     " then=Block#" + detail::num(si.then_blk) +
                     " elseifs=" + detail::num(si.elseifs.size()) +
                     " else=Stmt#" + detail::opt_num(si.else_));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtElseIf& se)
    {
        detail::line(os, it_, "StmtElseIf"
                     " cond=Expr#" + detail::num(se.cond) +
                     " blk=Block#" + detail::num(se.blk));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtElse& se)
    {
        detail::line(os, it_, "StmtElse"
                     " blk=Block#" + detail::num(se.blk));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtWhile& sw)
    {
        detail::line(os, it_, "StmtWhile"
                     " cond=Expr#" + detail::num(sw.cond) +
                     " body=Block#" + detail::num(sw.body));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtDoWhile& sd)
    {
        detail::line(os, it_, "StmtDoWhile"
                     " body=Block#" + detail::num(sd.body) +
                     " cond=Expr#" + detail::num(sd.cond));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtBreak&)
    {
        detail::line(os, it_, "StmtBreak");
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtContinue&)
    {
        detail::line(os, it_, "StmtContinue");
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtReturn& sr)
    {
        detail::line(os, it_, "StmtReturn"
                     " value=Expr#" + detail::opt_num(sr.value));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtVar& sv)
    {
        detail::line(os, it_, "StmtVar"
                     " name=" + ident(sv.name) +
                     " mut=" + detail::num(static_cast<uint32_t>(sv.mut)) +
                     " storage=" + detail::num(static_cast<uint32_t>(sv.storage)) +
                     " type=Type#" + detail::num(sv.type) +
                     " init=Expr#" + detail::opt_num(sv.init));
    }

    template <typename It>
    void DumpVisitor<It>::visit(StmtExpr& se)
    {
        detail::line(os, it_, "StmtExpr"
                     " expr=Expr#" + detail::num(se.expr));
    }
}

#endif //INZ_DUMP_VISITOR_HPP
