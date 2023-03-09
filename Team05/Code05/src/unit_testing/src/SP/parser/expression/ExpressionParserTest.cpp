#include "SP/SPTesting.h"
#include "SP/lexer/Lexer.h"
#include "SP/parser/expression/ExpressionParser.h"

using namespace sp;  // NOLINT

auto x = MakeVar("x");
auto y = MakeVar("y");
auto z = MakeVar("z");
auto lemon = MakeVar("lemon");

ast::ExprNodePtr CreateChain(std::vector<std::string> variables, Token op,
                             ast::ExprNodePtr prev);

TEST_CASE("Expression parser parses chain of plus") {
  auto test = CreateChain({"apple", "ranch"}, Token::kTokPlus, lemon->Copy());
  Lexer lxr("lemon + apple+ranch");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses chain of minus") {
  auto test =
      CreateChain({"apple", "ranch", "fowl"}, Token::kTokMinus, lemon->Copy());
  Lexer lxr("lemon - apple-ranch- fowl");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses brackets") {
  auto additions =
      CreateChain({"apple", "ranch"}, Token::kTokPlus, lemon->Copy());
  auto test =
      std::make_unique<ast::OpNode>(Token::kTokTimes, std::move(additions),
                                    std::make_unique<ast::VarNode>("x"));
  Lexer lxr("(lemon + apple+ranch) * x");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses chain mult") {
  auto test =
      CreateChain({"apple", "ranch", "fowl"}, Token::kTokTimes, lemon->Copy());
  Lexer lxr("lemon * apple*ranch* fowl");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses div chain into addition") {
  auto left =
      CreateChain({"apple", "ranch", "fowl"}, Token::kTokDiv, lemon->Copy());
  auto test = CreateChain({"orange", "apple", "john"}, Token::kTokPlus,
                          std::move(left));
  Lexer lxr("lemon/apple/ranch/ fowl+orange+apple+john");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses large mix") {
  auto t1 =
      std::make_unique<ast::OpNode>(Token::kTokTimes, y->Copy(), z->Copy());

  auto m1 = std::make_unique<ast::OpNode>(
      Token::kTokMod, z->Copy(), std::make_unique<ast::VarNode>("ost"));
  auto t2 =
      std::make_unique<ast::OpNode>(Token::kTokTimes, x->Copy(), std::move(t1));
  auto test = std::make_unique<ast::OpNode>(Token::kTokPlus, std::move(m1),
                                            std::move(t2));
  Lexer lxr("z%ost +  x * (y * z )");
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Expression parser parses large nested brackets") {
  Lexer lxr("((((x+y)-z)+z)*y)-lemon");

  auto add_x_y = CreateOp(x->Copy(), y->Copy(), Token::kTokPlus);
  auto sub_x_z = CreateOp(std::move(add_x_y), z->Copy(), Token::kTokMinus);
  auto add_z_z = CreateOp(std::move(sub_x_z), z->Copy(), Token::kTokPlus);
  auto mult_z_y = CreateOp(std::move(add_z_z), y->Copy(), Token::kTokTimes);
  auto sub_y_lemon =
      CreateOp(std::move(mult_z_y), lemon->Copy(), Token::kTokMinus);

  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*sub_y_lemon));
}

TEST_CASE("Expression parser const nodes") {
  Lexer lxr("1+2");
  auto one = MakeConst(1);
  auto two = MakeConst(2);
  auto res = CreateOp(one->Copy(), two->Copy(), Token::kTokPlus);
  ExpressionParser expr_parser;
  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*res));
}

TEST_CASE("Complex const nodes expression") {
  Lexer lxr("(1+x)-2 + y-3");
  auto one = MakeConst(1);
  auto two = MakeConst(2);
  auto three = MakeConst(3);
  auto inner_add = CreateOp(one->Copy(), x->Copy(), Token::kTokPlus);
  auto outer_sub = CreateOp(inner_add->Copy(), two->Copy(), Token::kTokMinus);
  auto outer_add = CreateOp(outer_sub->Copy(), y->Copy(), Token::kTokPlus);
  auto test = CreateOp(outer_add->Copy(), three->Copy(), Token::kTokMinus);

  ExpressionParser expr_parser;

  REQUIRE(expr_parser.parse(lxr)->DeepEquals(*test));
}

TEST_CASE("Invalid expressions throw exception") {
  Lexer lxr("lemon orange s + b");
  ExpressionParser expr_parser;
  REQUIRE_THROWS_AS(expr_parser.parse(lxr), ParseException);
}

ast::ExprNodePtr CreateChain(std::vector<std::string> variables, Token op,
                             ast::ExprNodePtr prev) {
  for (int i = 0; i < variables.size(); ++i) {
    prev = std::make_unique<ast::OpNode>(
        op, std::move(prev), std::make_unique<ast::VarNode>(variables[i]));
  }
  return std::move(prev);
}

void TestEquivalentString(std::string left, std::string right) {
  Lexer lxr(left);
  Lexer o_lxr(right);
  VectorLexer v_lxr(lxr);
  VectorLexer o_v_lxr(o_lxr);
  ExpressionParser parser;
  auto& res = parser.ParseStringExpr(v_lxr);
  auto& other = parser.ParseStringExpr(o_v_lxr);
  std::cout << res << std::endl;

  REQUIRE(res == other);
  REQUIRE(other == res);
}

void TestContainsString(std::string left, std::string right,
                        bool contains = true) {
  Lexer lxr(left);
  Lexer o_lxr(right);
  VectorLexer v_lxr(lxr);
  VectorLexer o_v_lxr(o_lxr);
  ExpressionParser parser;
  auto& res = parser.ParseStringExpr(v_lxr);
  auto& other = parser.ParseStringExpr(o_v_lxr);
  std::cout << res << std::endl;
  std::cout << other << std::endl;
  REQUIRE(res.Contains(other) == contains);
}

TEST_CASE("Parsing of string expression") {
  Lexer lxr(
      "Lemon + orange / 1000 + 10 - (11111 * 21312 - 23940) / applesauce + "
      "galatica");

  VectorLexer v_lxr(lxr);
  ExpressionParser parser;
  auto& res = parser.ParseStringExpr(v_lxr);
  std::cout << res << std::endl;
}

TEST_CASE("Verify left associative") {
  TestEquivalentString("(a + b) + c", "a + b + c");
}

TEST_CASE("Verify left associative with times") {
  TestEquivalentString("a * b * c", "(a*b) * c");
}

TEST_CASE("Verify simple equality") { TestEquivalentString("a", "(a)"); }

TEST_CASE("Verify simple equality with addition") {
  TestEquivalentString("a + b", "(a) + b");
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

TEST_CASE("Test on different strings") {
  TestContainsString("a", "b", false);
  TestContainsString("a", "(b)", false);
  TestContainsString("b", "(a)", false);
  TestContainsString("(b)", "a", false);
  TestContainsString("a + B - c", "a + b - c", false);
}

TEST_CASE("Test on different chains") { TestContainsString("a + b", "a"); }
