#include "SP/visitors/TNodeVisitor.h"

namespace sp {

void TNodeVisitor::VisitProgram(ast::ProgramNode* program_node) {
  PerformWork(program_node);
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void TNodeVisitor::VisitProc(ast::ProcNode* proc_node) {
  PerformWork(proc_node);
  proc_node->get_children()->AcceptVisitor(this);
}

void TNodeVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  PerformWork(stmtlst_node);
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void TNodeVisitor::VisitAssign(ast::AssignNode* assign_node) {
  PerformWork(assign_node);
}

void TNodeVisitor::VisitRead(ast::ReadNode* read_node) {
  PerformWork(read_node);
}

void TNodeVisitor::VisitPrint(ast::PrintNode* print_node) {
  PerformWork(print_node);
}

void TNodeVisitor::VisitIf(ast::IfNode* if_node) {
  PerformWork(if_node);
  if_node->get_cond()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
}

void TNodeVisitor::VisitWhile(ast::WhileNode* while_node) {
  PerformWork(while_node);
  while_node->get_cond()->AcceptVisitor(this);
  while_node->get_stmts()->AcceptVisitor(this);
}

void TNodeVisitor::VisitCall(ast::CallNode* call_node) {
  PerformWork(call_node);
}

void TNodeVisitor::VisitExpr(ast::ExprNode* expr_node) {
  PerformWork(expr_node);
}

void TNodeVisitor::VisitOpNode(ast::OpNode* op_node) {
  PerformWork(op_node);
  op_node->get_left()->AcceptVisitor(this);
  op_node->get_right()->AcceptVisitor(this);
}

void TNodeVisitor::VisitNot(ast::NotExprNode* not_expr_node) {
  PerformWork(not_expr_node);
  not_expr_node->get_cond()->AcceptVisitor(this);
}

void TNodeVisitor::VisitVar(ast::VarNode* var_node) {
  PerformWork(var_node);
}

void TNodeVisitor::VisitConst(ast::ConstNode* const_node) {
  PerformWork(const_node);
}

void TNodeVisitor::VisitDoubleCond(
    ast::DoubleCondExprNode* double_cond_expr_node) {
  PerformWork(double_cond_expr_node);
  double_cond_expr_node->get_left_cond()->AcceptVisitor(this);
  double_cond_expr_node->get_right_cond()->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelExpr(ast::RelExprNode* rel_expr_node) {
  PerformWork(rel_expr_node);
  rel_expr_node->get_left_factor()->AcceptVisitor(this);
  rel_expr_node->get_right_factor()->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelFactor(ast::RelFactor* rel_factor) {
  PerformWork(rel_factor);
  rel_factor->get_expr()->AcceptVisitor(this);
  rel_factor->get_ref()->AcceptVisitor(this);
}
}  // namespace sp
