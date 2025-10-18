#include <fstream>
#include <stack>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/ast.hpp"
#include "ast/nodes/visit/dump_visitor.hpp"

int main() {
    std::ifstream in("myfile.txt");
    Scanner scanner{&in}; // uses stdin by default; set a stream in your .l if needed
    ast::AST ast;
    ast::visitor::DumpVisitor visitor(std::cout);

    yy::parser p(scanner, ast);
    const int rc = p.parse();

    std::cout << "hello: " << rc << std::endl;

    if (rc == 0) {
        if (auto* prj = ast.get_project()) {
            for (auto* m : prj->modules) if (m) m->accept(visitor);
        }

    }

    return rc;
}
