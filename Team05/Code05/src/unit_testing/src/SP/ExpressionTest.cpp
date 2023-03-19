#include <catch.hpp>

#include "SP/SourceProcessor.h"

using namespace sp;  // NOLINT

// performing testing of the interaction endpoints
// exposed to QPS by SP
void TestContainsString(std::string expr, std::string test,
                        bool output = true) {
  auto res_expr = SourceProcessor::ParseExpression(expr);
  auto test_expr = SourceProcessor::ParseExpression(test);
  REQUIRE(res_expr->PartialMatch(*test_expr) == output);
}

void TestEqualString(std::string expr, std::string test, bool output = true) {
  auto res_expr = SourceProcessor::ParseExpression(expr);
  auto test_expr = SourceProcessor::ParseExpression(test);
  REQUIRE(res_expr->DeepEquals(*test_expr) == output);
  REQUIRE(test_expr->DeepEquals(*res_expr) == output);
}

TEST_CASE("Simple string contains var") { TestContainsString("a+b", "a"); }

TEST_CASE("Bracketed string contains var") {
  TestContainsString("((a) + (b)) * c", "c");
}

TEST_CASE("Nested string contains expression") {
  TestContainsString("a + b + c + d + e + f + g", "a + b + c + d");
  TestContainsString("a * b * c * d * e * f * g", "a * b * c * d");
  TestContainsString("a * b * c * d * e * f * g", "d * e * f * g", false);
}

TEST_CASE("Mixed multiplcation and plus") {
  TestContainsString("a + b * c + d", "b * c");
  TestContainsString("a + b * c + d", "a + b", false);
  TestContainsString("a - b / c + d", "  b/   c");
  TestContainsString("a - b / c + d", "  b*   c", false);
}

TEST_CASE("Bracketed with modulo") {
  TestContainsString("a + b % (c + d)", "c + d");
  TestContainsString("a + b % (c + d)", "b % c", false);
  TestContainsString("a + b % (c + d)", "b % c", false);
}

TEST_CASE("Equality test cases") {
  TestEqualString("a + b * c001 + a1d", "a + (b * c001) + a1d");
  TestEqualString("a - b", "(a) - (((b)))");
  TestEqualString("a / b", "(a) / ((b))");
  TestEqualString("(a / b) * c", "a / b * c");
  TestEqualString("(a / b) * c", "(a / b * c)");
  TestEqualString("(a / b) * c", "(a / b * c)");
}

TEST_CASE("Test on massive chain") {
  std::string massive_chain =
      "(a + b"
      "+ c) + (d - e) * k"
      "+ (((m - g)-k)-l) * k"
      "* ((j +d)*metal)";
  TestContainsString(massive_chain, "a+b");
  TestContainsString(massive_chain, "d-e");
  TestContainsString(massive_chain, "m-g-k");
  TestContainsString(massive_chain, "j+d");
  TestContainsString(massive_chain, "d*metal", false);
  TestContainsString(massive_chain, massive_chain);
  TestContainsString(massive_chain, "metal");
  TestContainsString(massive_chain, "j");
  TestContainsString(massive_chain, "a");
  TestContainsString(massive_chain, "d - e * k", false);
  TestContainsString(massive_chain, "(d - e) * k");
}

TEST_CASE("Test on different strings") {
  TestContainsString("a", "b", false);
  TestContainsString("a", "(b)", false);
  TestContainsString("b", "(a)", false);
  TestContainsString("(b)", "a", false);
  TestContainsString("a + B - c", "a + b - c", false);
}

TEST_CASE("Test on very flat div term") {
  TestContainsString("a / b * c + d + e + f + g", "c + d", false);
  TestContainsString("a / b * c + d + e + f + g", "f + g", false);
  TestContainsString("a / b * c + d + e + f + g", "a + b", false);
  TestContainsString("a * b * c + d + e + f + g", "a * b");
  TestContainsString("a * b * c + d + e + f + g", "b*c", false);
  TestContainsString("a * b + b * c", "b*c");
  TestContainsString("a * b + b * c", "a*b");
  TestContainsString("a * b + b * c", "b+b", false);
  TestContainsString("a", "b", false);
}

TEST_CASE("Test on equiv strings") {
  TestContainsString("a", "a");
  TestContainsString("a", "(a)");
  TestContainsString("(a)", "(a)");
  TestContainsString("(a) / (b) * (c) + (d) + (e) + (f) + (g)",
                     "a / b * c + d + e + f + g");

  TestContainsString("apple - sauce + 100 * 2000",
                     "(apple - sauce) + ((100) * (2000))");
}
TEST_CASE("Verify simple equality with addition") {
  TestEqualString("a + b", "(a) + b");
}

TEST_CASE("Test contains string addition") {
  TestContainsString("a + b", "(a) + b");
}

TEST_CASE("Test nested contains") {
  TestContainsString("a + b + c + d + e + f + g", "(a) + b");
}

TEST_CASE("Test on complex term") {
  TestContainsString("(((a * b) * c) * d) + (k - b)", "(a*b)");
}

TEST_CASE("Test on deep term") {
  TestContainsString("a + (b + c)", "(a + b) + c", false);
}

TEST_CASE("Test on very flat term") {
  TestContainsString("a + b + c + d + e + f + g", "c + d", false);
  TestContainsString("a + b + c + d + e + f + g", "f + g", false);
  TestContainsString("a + b + c + d + e + f + g", "a + b");
}