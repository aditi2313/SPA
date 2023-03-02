#include "SPTesting.h"

std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node) {
  return std::make_unique<RelFactor>(std::move(expr_node));
}

std::unique_ptr<VarNode> MakeVar(std::string var_name) {
  return std::make_unique<VarNode>(var_name);
}

std::unique_ptr<RelFactor> InitialiseAdd() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto add_expr =
      std::make_unique<OpNode>(Token::kTokPlus, a->Copy(), b->Copy());
  return MakeFactor(std::move(add_expr));
}

std::unique_ptr<RelFactor> InitialiseSub() {
  auto a = MakeVar("a");
  auto b = MakeVar("b");
  auto minus_expr =
      std::make_unique<OpNode>(Token::kTokMinus, a->Copy(), b->Copy());
  return MakeFactor(std::move(minus_expr));
}

ExprNodePtr CreateOp(ExprNodePtr left, ExprNodePtr right, Token tok) {
  return std::make_unique<OpNode>(tok, std::move(left), std::move(right));
}

ExprNodePtr MakeConst(int v) {
  return std::make_unique<ConstNode>(ConstNode(v));
}

std::unique_ptr<ReadNode> MakeRead(std::string var_name, int line) {
  return std::make_unique<ReadNode>(MakeVar(var_name), line);
}

std::unique_ptr<PrintNode> MakePrint(std::string var_name, int line) {
  return std::make_unique<PrintNode>(MakeVar(var_name), line);
}

std::unique_ptr<IfNode> MakeIf(int line) { return nullptr; }

std::unique_ptr<WhileNode> MakeWhile(int line) { return nullptr; }
