#pragma once

#include <memory>
#include <string>
#include <utility>
#include <catch.hpp>
#include "SP/parser/expression/TermParser.h"
#include "SP/lexer/Lexer.h"

// factor: var_name | const_value | '(' expr ')'
TEST_CASE("Term * factor should return TimesNode") {
  sp::Lexer lexer("bd * c");
  sp::TermParser term_parser;
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("bd"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("c"));
  auto expected_result = std::make_unique<ast::TimesNode>(
      ast::TimesNode(std::move(lhs), std::move(rhs)));

  auto actual_result = term_parser.parse(lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Term / factor should return DivNode") {
  sp::Lexer lexer("abdcde / fu");
  sp::TermParser term_parser;
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("abdcde"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("fu"));
  auto expected_result = std::make_unique<ast::DivNode>(
      ast::DivNode(std::move(lhs), std::move(rhs)));

  auto actual_result = term_parser.parse(lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Term % factor should return ModNode") {
  sp::Lexer lexer("hashbrown % lover");
  sp::TermParser term_parser;
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("hashbrown"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("lover"));
  auto expected_result = std::make_unique<ast::ModNode>(
      ast::ModNode(std::move(lhs), std::move(rhs)));

  auto actual_result = term_parser.parse(lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Single variable should return VarNode") {
  sp::Lexer lexer("single;");
  sp::TermParser term_parser;
  auto expected_result = std::make_unique<ast::VarNode>(ast::VarNode("single"));

  auto actual_result = term_parser.parse(lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Single constant should return ConstNode") {
  sp::Lexer lexer("1234;");
  sp::TermParser term_parser;
  auto expected_result = std::make_unique<ast::ConstNode>(ast::ConstNode(1234));

  auto actual_result = term_parser.parse(lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}
