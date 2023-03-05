#include "SP/visitors/TNodeVisitor.h"

namespace sp {

void TNodeVisitor::VisitProgram(ast::ProgramNode* program_node) {
  Process(program_node);
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
  ProcessAfter(program_node);
}

void TNodeVisitor::VisitProc(ast::ProcNode* proc_node) {
  Process(proc_node);
  auto& children = proc_node->get_children();
  children->AcceptVisitor(this);
}

void TNodeVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  Process(stmtlst_node);
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
  ProcessAft(stmtlst_node);
}

void TNodeVisitor::VisitAssign(ast::AssignNode* assign_node) {
  Process(assign_node);
}

void TNodeVisitor::VisitRead(ast::ReadNode* read_node) { Process(read_node); }

void TNodeVisitor::VisitPrint(ast::PrintNode* print_node) {
  Process(print_node);
}

void TNodeVisitor::VisitIf(ast::IfNode* if_node) {
  Process(if_node);
  auto& cond_node = if_node->get_cond();
  cond_node->AcceptVisitor(this);

  auto& then_stmt_lst = if_node->get_then();
  then_stmt_lst->AcceptVisitor(this);

  auto& else_stmt_lst = if_node->get_else();
  else_stmt_lst->AcceptVisitor(this);

  ProcessAft(if_node);
}

void TNodeVisitor::VisitWhile(ast::WhileNode* while_node) {
  Process(while_node);
  auto& cond_node = while_node->get_cond();
  cond_node->AcceptVisitor(this);

  auto& stmt_lst = while_node->get_stmts();
  stmt_lst->AcceptVisitor(this);

  ProcessAft(while_node);
}

void TNodeVisitor::VisitCall(ast::CallNode* call_node) { Process(call_node); }

void TNodeVisitor::VisitExpr(ast::ExprNode* expr_node) { Process(expr_node); }

void TNodeVisitor::VisitOpNode(ast::OpNode* op_node) {
  Process(op_node);

  auto& left_expr = op_node->get_left();
  left_expr->AcceptVisitor(this);

  auto& right_expr = op_node->get_right();
  right_expr->AcceptVisitor(this);
}

void TNodeVisitor::VisitNot(ast::NotExprNode* not_expr_node) {
  Process(not_expr_node);

  auto& cond_expr = not_expr_node->get_cond();
  cond_expr->AcceptVisitor(this);
}

void TNodeVisitor::VisitVar(ast::VarNode* var_node) { Process(var_node); }

void TNodeVisitor::VisitConst(ast::ConstNode* const_node) {
  Process(const_node);
}

void TNodeVisitor::VisitDoubleCond(
    ast::DoubleCondExprNode* double_cond_expr_node) {
  Process(double_cond_expr_node);

  auto& left_cond_expr = double_cond_expr_node->get_left_cond();
  left_cond_expr->AcceptVisitor(this);

  auto& right_cond_expr = double_cond_expr_node->get_right_cond();
  right_cond_expr->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelExpr(ast::RelExprNode* rel_expr_node) {
  Process(rel_expr_node);

  auto& left_factor = rel_expr_node->get_left_factor();
  left_factor->AcceptVisitor(this);

  auto& right_factor = rel_expr_node->get_right_factor();
  right_factor->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelFactor(ast::RelFactor* rel_factor) {
  Process(rel_factor);

  auto& expr = rel_factor->get_expr();
  expr->AcceptVisitor(this);
}
}  // namespace sp
