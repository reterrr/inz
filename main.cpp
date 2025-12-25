#include <filesystem>
#include <fstream>

#include "compiler_context.hpp"
#include "translation.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/ast.hpp"
#include "ast/nodes/visit/dump_visitor.hpp"
#include "hir/defer_visit.hpp"
#include "hir/iterator.hpp"
#include "hir/lowerer.hpp"

// #include "sema/sema.hpp"


int main()
{
    CompilerContext compilerContext;
    compilerContext.files.emplace_back("myfile.kl");

    ast::Ast ast;
    Translation translation;
    //ast::visitor::DumpVisitor visitor{std::cout, compilerContext};

    //sema::Sema sema(ast);

    for (const auto& file : compilerContext.files)
    {
        std::ifstream in{file};
        Scanner scanner{compilerContext, &in};
        yy::parser p{scanner, ast, translation};
        if (const int rc = p.parse(); rc == 0)
        {
            hir::Lowerer lowerer{ast, translation};
            lowerer.lower();
            hir::Arena ar = lowerer.arena_;

            hir::DIterator it{ar, ast.node_count()};
            hir::DumpVisitor d{it, compilerContext};
            it.setAVisitor(d);
            it.start_place(hir::ArenaKinds::modules, 0);
            it.start_apply_inline();
            //sema.run();
            // if (auto* prj{ast.get_project()})
            // {
            //     prj->accept(visitor);
            // }
        }
    }

    return 0;
}
