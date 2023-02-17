#include "SP/SPTesting.h"

template <class TestedClass>
void TestRelExprClass(std::string input, sp::RelExprParser& parser) {
  Lexer lxr("a + b " + input + " a - b");
  auto add = InitialiseAdd();
  auto sub = InitialiseSub();
  auto expected = std::make_unique<TestedClass>(std::move(add), std::move(sub));
  auto result = parser.parse(lxr);
  REQUIRE(expected->DeepEquals(*result));
}

TEST_CASE("Less than expression parses") {
  RelExprParser parser;
  TestRelExprClass<LessThanNode>("<", parser);
}

TEST_CASE("More than expression parses") {
  RelExprParser parser;
  TestRelExprClass<MoreThanNode>(">", parser);
}

TEST_CASE("Equal expression parses") {
  RelExprParser parser;
  TestRelExprClass<EqualNode>("==", parser);
}

TEST_CASE("Less than equal expression parses") {
  RelExprParser parser;
  TestRelExprClass<LessThanEqualNode>("<=", parser);
}

TEST_CASE("More than equal expression parses") {
  RelExprParser parser;
  TestRelExprClass<MoreThanEqualNode>(">=", parser);
}
