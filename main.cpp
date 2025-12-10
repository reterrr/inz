#include <fstream>
#include <stack>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/ast.hpp"
#include "ast/nodes/visit/dump_visitor.hpp"

#include "sema/sema.hpp"

int main()
{
    std::ifstream in("myfile.txt");
    Scanner scanner{&in}; // uses stdin by default; set a stream in your .l if needed
    ast::AST ast;
    ast::visitor::DumpVisitor visitor(std::cout);
    sema::Sema sema(ast);

    yy::parser p(scanner, ast);
    const int rc = p.parse();

    if (rc == 0)
    {
        sema.run();
        if (auto* prj = ast.get_project())
        {
            prj->accept(visitor);
        }
    }

    return rc;
}
