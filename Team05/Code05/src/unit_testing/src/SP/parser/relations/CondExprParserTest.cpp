#include "RelationTesting.h"

void TestCondExpr(Lexer& lxr, const CondExprNode& expected);

TEST_CASE("And expression parses") {
  Lexer lxr("(a + b == a - b) && ( a + b <= a - b )");
  auto equal = std::make_unique<EqualNode>(std::move(InitialiseAdd()),
                                           std::move(InitialiseSub()));
  auto other_less = std::make_unique<LessThanEqualNode>(
      std::move(InitialiseAdd()), std::move(InitialiseSub()));
  auto overall =
      std::make_unique<AndExprNode>(std::move(equal), std::move(other_less));
  TestCondExpr(lxr, *overall);
}

TEST_CASE("OR expression parses") {
  Lexer lxr("(a + b == a-b ) || (a + b <=a-b )");
  auto equal = std::make_unique<EqualNode>(std::move(InitialiseAdd()),
                                           std::move(InitialiseSub()));
  auto other_less = std::make_unique<LessThanEqualNode>(
      std::move(InitialiseAdd()), std::move(InitialiseSub()));
  auto overall =
      std::make_unique<OrExprNode>(std::move(equal), std::move(other_less));
  TestCondExpr(lxr, *overall);
}

TEST_CASE("NOT expression parses") {
  Lexer lxr("!(a+b == a-b)");
  auto not_expr = std::make_unique<NotExprNode>(std::make_unique<EqualNode>(
      std::move(InitialiseAdd()), std::move(InitialiseSub())));
  TestCondExpr(lxr, *not_expr);
}

// testing parsing with error
TEST_CASE("Invalid expression throws error") {
  Lexer lxr("(a + b & a-b) || (a+b <=a-b)");
  CondExprParser parser;
  REQUIRE_THROWS_AS(parser.parse(lxr), std::exception);
}

void TestCondExpr(Lexer& lxr, const CondExprNode& expected) {
  CondExprParser parser;
  auto result = parser.parse(lxr);
  REQUIRE(result->DeepEquals(expected));
}
