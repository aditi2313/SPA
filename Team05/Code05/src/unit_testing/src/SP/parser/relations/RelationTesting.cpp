#include "RelationTesting.h"

std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node) {
  return std::make_unique<RelFactor>(std::move(expr_node));
}

std::unique_ptr<VarNode> MakeVar(std::string var_name) {
  return std::make_unique<VarNode>(var_name);
}

std::unique_ptr<RelFactor> InitialiseAdd() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto add_expr = std::make_unique<PlusNode>(a->CopyFactor(), b->CopyFactor());
  return MakeFactor(std::move(add_expr));
}

std::unique_ptr<RelFactor> InitialiseSub() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto minus_expr =
      std::make_unique<MinusNode>(a->CopyFactor(), b->CopyFactor());
  return MakeFactor(std::move(minus_expr));
}
