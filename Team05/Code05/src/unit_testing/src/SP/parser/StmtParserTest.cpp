#include <catch.hpp>

#include "SP/lexer/Lexer.h"
#include "SP/parser/stmts/AssignParser.h"
#include "SP/parser/stmts/StatementParser.h"

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
