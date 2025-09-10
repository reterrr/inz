%{
 #include "generated/token.hpp"
 #include "lexer.hpp"
 #include "semantic_value.hpp"

 uint64_t offset = 0;
 uint64_t column = 1;
%}

%option c++
%option yyclass="Scanner"
%option noyywrap
%option yylineno

%%

"if"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_IF,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_IF;
              }
"while"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_WHILE,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_WHILE;
              }
"do"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_DO,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_DO;
              }
"int"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_INT,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_INT;
              }
"bigint"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_BIGINT,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_BIGINT;
              }
"magicint"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_MAGICINT,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_MAGICINT;
              }
"double"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_DOUBLE,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_DOUBLE;
              }
"bool"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_BOOL,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_BOOL;
              }
"void"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_VOID,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_VOID;
              }
"string"   {
                 uint64_t start_offset = offset;
                 offset += yyleng;
                 uint64_t end_offset = offset - 1;
                 uint64_t start_column = column;
                 column += yyleng;
                 auto token = Token::Value(
                     Token::Type::TOK_STRING,
                     std::string(yytext, yyleng),
                     std::monostate{},  // no semantic value
                     yylineno,
                     start_column,
                     start_offset,
                     end_offset
                 );
                 static_cast<Scanner*>(this)->setCurrentToken(token);
                 return Token::Type::TOK_STRING;
              }


"("   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_LPAR,
                                         "(",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_LPAR;
                                 }
")"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_RPAR,
                                         ")",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_RPAR;
                                 }
"["   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_LSUBSCRIPT,
                                         "[",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_LSUBSCRIPT;
                                 }
"]"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_RSUBSCRIPT,
                                         "]",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_RSUBSCRIPT;
                                 }
"."   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_SELECTOR,
                                         ".",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_SELECTOR;
                                 }
"!"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_NEGATION,
                                         "!",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_NEGATION;
                                 }
"-"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_NEG,
                                         "-",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_NEG;
                                 }
"*"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_STAR,
                                         "*",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_STAR;
                                 }
"/"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_SLASH,
                                         "/",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_SLASH;
                                 }
"%"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_MODULO,
                                         "%",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_MODULO;
                                 }
"+"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_PLUS,
                                         "+",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_PLUS;
                                 }
"-"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_MINUS,
                                         "-",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_MINUS;
                                 }
"<"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_LESS,
                                         "<",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_LESS;
                                 }
"<="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_LEQ,
                                         "<=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_LEQ;
                                 }
">"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_GREATER,
                                         ">",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_GREATER;
                                 }
">="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_GEQ,
                                         ">=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_GEQ;
                                 }
"=="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_EQUAL,
                                         "==",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_EQUAL;
                                 }
"!="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_NEQUAL,
                                         "!=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_NEQUAL;
                                 }
"&&"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_BOOL_AND,
                                         "&&",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_BOOL_AND;
                                 }
"||"   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_BOOL_OR,
                                         "||",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_BOOL_OR;
                                 }
"="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_ASSIGN,
                                         "=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_ASSIGN;
                                 }
"+="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_PLUS_ASSIGN,
                                         "+=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_PLUS_ASSIGN;
                                 }
"-="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_MIN_ASSIGN,
                                         "-=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_MIN_ASSIGN;
                                 }
"*="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_MUL_ASSIGN,
                                         "*=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_MUL_ASSIGN;
                                 }
"/="   {
                                     uint64_t start_offset = offset;
                                     offset += yyleng;
                                     uint64_t end_offset = offset - 1;
                                     uint64_t start_column = column;
                                     column += yyleng;
                                     auto token = Token::Value(
                                         Token::Type::TOK_DIV_ASSIGN,
                                         "/=",
                                         std::string(yytext, yyleng),
                                         yylineno,
                                         start_column,
                                         start_offset,
                                         end_offset
                                     );
                                     static_cast<Scanner*>(this)->setCurrentToken(token);
                                     return Token::Type::TOK_DIV_ASSIGN;
                                 }

"("   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_LPAR,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_LPAR;
                                 }
")"   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_RPAR,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_RPAR;
                                 }
"{"   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_LCBRA,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_LCBRA;
                                 }
"}"   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_RCBRA,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_RCBRA;
                                 }
";"   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_SMCLN,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_SMCLN;
                                 }
"."   {
                                  uint64_t start_offset = offset;
                                  offset += yyleng;
                                  uint64_t end_offset = offset - 1;
                                  uint64_t start_column = column;
                                  column += yyleng;
                                  auto token = Token::Value(
                                      Token::Type::TOK_DOT,
                                      std::string(yytext, yyleng),
                                      std::monostate{},
                                      yylineno,
                                      start_column,
                                      start_offset,
                                      end_offset
                                  );
                                  static_cast<Scanner*>(this)->setCurrentToken(token);
                                  return Token::Type::TOK_DOT;
                                 }

[a-zA-Z_][a-zA-Z0-9_]*   {
                               uint64_t start_offset = offset;
                               offset += yyleng;
                               uint64_t end_offset = offset - 1;
                               uint64_t start_column = column;
                               column += yyleng;
                               auto token = Token::Value(
                                   Token::Type::TOK_IDENTIFIER,
                                   std::string(yytext, yyleng),
                                   std::string(yytext, yyleng),
                                   yylineno,
                                   start_column,
                                   start_offset,
                                   end_offset
                               );
                               static_cast<Scanner*>(this)->setCurrentToken(token);
                               return Token::Type::TOK_IDENTIFIER;
                         }

\"([^\\\"]|\\.)*\"       {
                                uint64_t start_offset = offset;
                                offset += yyleng;
                                uint64_t end_offset = offset - 1;
                                uint64_t start_column = column;
                                column += yyleng;
                                auto token = Token::Value(
                                    Token::Type::TOK_STRING_LITERAL,
                                    std::string(yytext, yyleng),
                                    std::string(yytext, yyleng),
                                    yylineno,
                                    start_column,
                                    start_offset,
                                    end_offset
                                );
                                static_cast<Scanner*>(this)->setCurrentToken(token);
                                return Token::Type::TOK_STRING_LITERAL;
                         }

[0-9]+(?:\.[0-9]+)?      {
                               uint64_t start_offset = offset;
                               offset += yyleng;
                               uint64_t end_offset = offset - 1;
                               uint64_t start_column = column;
                               column += yyleng;
                               auto token = Token::Value(
                                   // if there's a dot it's a float, else int
                                   (strchr(yytext, '.') ? Token::Type::TOK_FLOAT_LITERAL
                                                         : Token::Type::TOK_INT_LITERAL),
                                   std::string(yytext, yyleng),
                                   std::string(yytext, yyleng),
                                   yylineno,
                                   start_column,
                                   start_offset,
                                   end_offset
                               );
                               static_cast<Scanner*>(this)->setCurrentToken(token);
                               return token.type_;
                         }

[ \t]+            { offset += yyleng; column += yyleng; /* skip spaces/tabs */ }
\n                { offset += yyleng; column = 1;              /* newline */ }
\r                { /* ignore CR */ }
.                 { /* skip unknown */ }

<<EOF>>           {
                      auto token = Token::Value(
                          Token::Type::TOK_END,
                          std::string("", 0),
                          std::monostate{},
                          yylineno,
                          column,
                          offset,
                          offset
                      );
                      static_cast<Scanner*>(this)->setCurrentToken(token);
                      return Token::Type::TOK_END;
                  }
%%