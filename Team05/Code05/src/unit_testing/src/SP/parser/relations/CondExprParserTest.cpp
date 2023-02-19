#include "SP/SPTesting.h"

void TestCondExpr(Lexer& lxr, const CondExprNode& expected);

template <class T>
void RequiresException(std::string);

TEST_CASE("AND expression parses") {
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

TEST_CASE("(x) >= 0") { 
  Lexer lxr("(x) >= 0)");
  CondExprParser parser;
  parser.parse(lxr);

}

// testing parsing with error
TEST_CASE("Invalid expression throws error") {
  SECTION("Invalid token") {
    RequiresException<std::exception>("(a + b & a-b) || (a+b <=a-b)");
  }
  SECTION("Invalid bracket placement") {
    RequiresException<std::exception>("(a + b) && a - b || (a - b)");
    RequiresException<std::exception>("(a+b == a-b || (a-b)");
  }
  SECTION("Invalid syntax") {
    RequiresException<ParseException>("(a+b && a-b)");
  }
}

template <class T>
void RequiresException(std::string val) {
  Lexer lxr(val);
  CondExprParser parser;
  REQUIRE_THROWS_AS(parser.parse(lxr), T);
}

void TestCondExpr(Lexer& lxr, const CondExprNode& expected) {
  CondExprParser parser;
  auto result = parser.parse(lxr);
  REQUIRE(result->DeepEquals(expected));
}
