#include "SPTesting.h"

#include <functional>

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

std::unique_ptr<StmtLstNode> make_stmts(
    std::function<std::unique_ptr<StmtNode>(int)> stmt_creator, int start,
    int end) {
  auto res = std::make_unique<StmtLstNode>(stmt_creator(start));
  for (int i = start + 1; i <= end; ++i) {
    res->add_stmt(stmt_creator(i));
  }
  return res;
}
std::unique_ptr<IfNode> MakeIf(int line, int s1, int e1, int s2, int e2) {
  auto cond = std::make_unique<LessThanEqualNode>(
      LessThanEqualNode(InitialiseSub(), InitialiseAdd()));
  auto stmts1 = make_stmts([&](int v) { return MakePrint("x", v); }, s1, e1);
  auto stmts2 = make_stmts([&](int v) { return MakePrint("x", v); }, s2, e2);
  return std::make_unique<IfNode>(std::move(cond), std::move(stmts1),
                                  std::move(stmts2), line);
}

std::unique_ptr<WhileNode> MakeWhile(int line, int start, int end) {
  auto cond = std::make_unique<LessThanEqualNode>(
      LessThanEqualNode(InitialiseSub(), InitialiseAdd()));
  auto stmts = make_stmts([&](int v) { return MakeRead("x", v); }, start, end);
  return std::make_unique<WhileNode>(
      WhileNode(std::move(cond), std::move(stmts), line));
}
