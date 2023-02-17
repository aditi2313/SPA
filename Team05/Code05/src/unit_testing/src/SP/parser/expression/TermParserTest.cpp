#pragma once
#include "SP/SPTesting.h"
#include "SP/lexer/Lexer.h"
#include "SP/parser/expression/TermParser.h"

// term: term '*' factor | term '/' factor | term '%' factor | factor
TEST_CASE("Term * factor should return TimesNode") {
  sp::Lexer lexer("bd * c");
  sp::TermParser term_parser;
  sp::VectorLexer v_lexer(lexer);
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("bd"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("c"));
  auto expected_result = std::make_unique<ast::OpNode>(
      ast::OpNode(sp::Token::kTokTimes, std::move(lhs), std::move(rhs)));

  auto actual_result = term_parser.parse(v_lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Term / factor should return DivNode") {
  sp::Lexer lexer("abdcde / fu");
  sp::TermParser term_parser;
  sp::VectorLexer v_lexer(lexer);
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("abdcde"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("fu"));
  auto expected_result = std::make_unique<ast::OpNode>(
      sp::Token::kTokDiv, std::move(lhs), std::move(rhs));

  auto actual_result = term_parser.parse(v_lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Term % factor should return ModNode") {
  auto actual_result = term_parser.parse(lexer);
  sp::VectorLexer v_lexer(lexer);
  sp::TermParser term_parser;
  auto lhs = std::make_unique<ast::VarNode>(ast::VarNode("hashbrown"));
  auto rhs = std::make_unique<ast::VarNode>(ast::VarNode("lover"));
  auto expected_result = std::make_unique<ast::OpNode>(

  auto actual_result = term_parser.parse(v_lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Single variable should return VarNode") {
  sp::Lexer lexer("single;");
  sp::VectorLexer v_lexer(lexer);
  sp::TermParser term_parser;
  auto expected_result = std::make_unique<ast::VarNode>(ast::VarNode("single"));

  auto actual_result = term_parser.parse(v_lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}

TEST_CASE("Single constant should return ConstNode") {
  sp::Lexer lexer("1234;");
  sp::TermParser term_parser;
  sp::VectorLexer v_lexer(lexer);
  auto expected_result = std::make_unique<ast::ConstNode>(ast::ConstNode(1234));

  auto actual_result = term_parser.parse(v_lexer);

  REQUIRE(actual_result->DeepEquals(*expected_result));
}
