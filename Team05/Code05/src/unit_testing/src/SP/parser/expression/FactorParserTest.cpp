#pragma once

#include <memory>
#include <string>
#include <catch.hpp>
#include "SP/parser/expression/FactorParser.h"
#include "SP/lexer/Lexer.h"

// INTEGER : 0 | NZDIGIT ( DIGIT )*
// NAME: LETTER (LETTER | DIGIT)*
// factor: var_name | const_value | '(' expr ')'

TEST_CASE("Valid variable name with only letters should return VarNode") {
  sp::Lexer lxr = sp::Lexer("abcde");
  sp::FactorParser factor_parser;
  auto expected_result = std::make_unique<ast::VarNode>(ast::VarNode("abcde"));

  auto actual_result = factor_parser.parse(lxr);

  REQUIRE(expected_result->DeepEquals(*actual_result));
}

TEST_CASE("Valid variable name with letters and digits should return VarNode") {
  sp::Lexer lxr = sp::Lexer("a121d");
  sp::FactorParser factor_parser;
  auto expected_result = std::make_unique<ast::VarNode>(ast::VarNode("a121d"));

  auto actual_result = factor_parser.parse(lxr);

  REQUIRE(expected_result->DeepEquals(*actual_result));
}

TEST_CASE("Valid constant should return ConstNode 123") {
  sp::Lexer lxr = sp::Lexer("123");
  sp::FactorParser factor_parser;
  auto expected_result = std::make_unique<ast::ConstNode>(ast::ConstNode(123));

  auto actual_result = factor_parser.parse(lxr);

  REQUIRE(expected_result->DeepEquals(*actual_result));
}

TEST_CASE("Valid constant should return ConstNode 0") {
  sp::Lexer lxr = sp::Lexer("0");
  sp::FactorParser factor_parser;
  auto expected_result = std::make_unique<ast::ConstNode>(ast::ConstNode(0));

  auto actual_result = factor_parser.parse(lxr);

  REQUIRE(expected_result->DeepEquals(*actual_result));
}
