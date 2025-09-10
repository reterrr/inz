#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "ast/ast.hpp"

int main() {
    Scanner scanner;      // uses stdin by default; set a stream in your .l if needed
    ast::AST ast;

    yy::parser p(scanner, ast);
    int rc = p.parse();

    return rc;
}
