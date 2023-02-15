#include <catch.hpp>

#include "SP/lexer/Lexer.h"
#include "SP/parser/stmts/AssignParser.h"
#include "SP/parser/stmts/IfParser.h"
#include "SP/parser/stmts/StatementParser.h"
#include "SP/parser/stmts/WhileParser.h"

using namespace sp;  // NOLINT

TEST_CASE("Test parsing of assignment") {
  Lexer lxr("a = a + b;");
  StatementParser parser;
  parser.parse(lxr);
}

TEST_CASE("Test parsing of read") {
  Lexer lxr("read a;");
  StatementParser parser;
  parser.parse(lxr);
}

TEST_CASE("Test parsing of print") {
  Lexer lxr("print a;");
  StatementParser parser;
  parser.parse(lxr);
}

TEST_CASE("Test parsing of if") {
  Lexer lxr("if (a+x < a - x) then {read a; print a;  } else { read a; }");
  IfParser parser;
  parser.parse(lxr);
}

TEST_CASE("Test parsing of While") {
  Lexer lxr("while (a+b >x-a) { read a; print a; }");
  WhileParser parser;
  parser.parse(lxr);
}
