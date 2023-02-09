#include <catch.hpp>
#include <string>

#include "SP/Lexer.h"
#include "SP/parser/relations/CondExprParser.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/relations/RelExprNode.h"

using namespace ast;  // NOLINT
using sp::CondExprParser;
using sp::Lexer;

void TestCondExpr(Lexer& lxr, const CondExprNode& expected);

// Initialisation
std::unique_ptr<VarNode> MakeVar(std::string var_name);
std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node);
std::unique_ptr<RelFactor> InitialseSub();
std::unique_ptr<RelFactor> InitialiseAdd();

TEST_CASE("Less than expression parses") {
  // initialising test variables
  Lexer lxr("a + b < a - b");
  auto add = InitialiseAdd();
  auto sub = InitialseSub();
  auto less = std::make_unique<LessThanNode>(std::move(add), std::move(sub));

  TestCondExpr(lxr, *less);
}

TEST_CASE("More than expression parses") {
  Lexer lxr("a + b > a - b");
  auto equal = std::make_unique<MoreThanNode>(std::move(InitialiseAdd()),
                                              std::move(InitialseSub()));
  TestCondExpr(lxr, *equal);
}

TEST_CASE("Equal expression parses") {
  Lexer lxr("a + b == a - b");
  auto equal = std::make_unique<EqualNode>(std::move(InitialiseAdd()),
                                           std::move(InitialseSub()));
  TestCondExpr(lxr, *equal);
}

TEST_CASE("Less than equal expression parses") {
  Lexer lxr("a + b <= a - b");
  auto equal = std::make_unique<LessThanEqualNode>(std::move(InitialiseAdd()),
                                                   std::move(InitialseSub()));
  TestCondExpr(lxr, *equal);
}

TEST_CASE("More than equal expression parses") {
  Lexer lxr("a + b >= a - b");
  auto equal = std::make_unique<MoreThanEqualNode>(std::move(InitialiseAdd()),
                                                   std::move(InitialseSub()));
  TestCondExpr(lxr, *equal);
}

TEST_CASE("And expression parses") {
  Lexer lxr("(a + b == a - b) && ( a + b <= a - b )");
  auto equal = std::make_unique<EqualNode>(std::move(InitialiseAdd()),
                                                   std::move(InitialseSub()));
  auto other_less = std::make_unique<LessThanEqualNode>(
      std::move(InitialiseAdd()), std::move(InitialseSub()));
  auto overall =
      std::make_unique<AndExprNode>(std::move(equal), std::move(other_less));
  TestCondExpr(lxr, *overall);
}

TEST_CASE("OR expression parses") {
  Lexer lxr("(a + b == a-b ) || (a + b <= a - b )");
  auto equal = std::make_unique<EqualNode>(std::move(InitialiseAdd()),
                                                   std::move(InitialseSub()));
  auto other_less = std::make_unique<LessThanEqualNode>(
      std::move(InitialiseAdd()), std::move(InitialseSub()));
  auto overall =
      std::make_unique<OrExprNode>(std::move(equal), std::move(other_less));
  TestCondExpr(lxr, *overall);
}

std::unique_ptr<RelFactor> InitialiseAdd() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto add_expr = std::make_unique<PlusNode>(a->CopyFactor(), b->CopyFactor());
  return MakeFactor(std::move(add_expr));
}

std::unique_ptr<RelFactor> InitialseSub() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto minus_expr =
      std::make_unique<MinusNode>(a->CopyFactor(), b->CopyFactor());
  return MakeFactor(std::move(minus_expr));
}

std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node) {
  return std::make_unique<RelFactor>(std::move(expr_node));
}

std::unique_ptr<VarNode> MakeVar(std::string var_name) {
  return std::make_unique<VarNode>(var_name);
}

void TestCondExpr(Lexer& lxr, const CondExprNode& expected) {
  CondExprParser parser;
  auto result = parser.parse(lxr);
  REQUIRE(result->DeepEquals(expected));
}
