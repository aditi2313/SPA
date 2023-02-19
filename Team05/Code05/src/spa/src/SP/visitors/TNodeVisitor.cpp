#include "SP/visitors/TNodeVisitor.h"

namespace sp {

void TNodeVisitor::VisitProgram(ast::ProgramNode* program_node) {
  Process(program_node);
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void TNodeVisitor::VisitProc(ast::ProcNode* proc_node) {
  Process(proc_node);
  proc_node->get_children()->AcceptVisitor(this);
}

void TNodeVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  Process(stmtlst_node);
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void TNodeVisitor::VisitAssign(ast::AssignNode* assign_node) {
  Process(assign_node);
}

void TNodeVisitor::VisitRead(ast::ReadNode* read_node) {
  Process(read_node);
}

void TNodeVisitor::VisitPrint(ast::PrintNode* print_node) {
  Process(print_node);
}

void TNodeVisitor::VisitIf(ast::IfNode* if_node) {  
  if_node->get_cond()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
  Process(if_node);
}

void TNodeVisitor::VisitWhile(ast::WhileNode* while_node) {  
  while_node->get_cond()->AcceptVisitor(this);
  while_node->get_stmts()->AcceptVisitor(this);
  Process(while_node);
}

void TNodeVisitor::VisitCall(ast::CallNode* call_node) {
  Process(call_node);
}

void TNodeVisitor::VisitExpr(ast::ExprNode* expr_node) {
  Process(expr_node);
}

void TNodeVisitor::VisitOpNode(ast::OpNode* op_node) {
  Process(op_node);
  op_node->get_left()->AcceptVisitor(this);
  op_node->get_right()->AcceptVisitor(this);
}

void TNodeVisitor::VisitNot(ast::NotExprNode* not_expr_node) {
  Process(not_expr_node);
  not_expr_node->get_cond()->AcceptVisitor(this);
}

void TNodeVisitor::VisitVar(ast::VarNode* var_node) {
  Process(var_node);
}

void TNodeVisitor::VisitConst(ast::ConstNode* const_node) {
  Process(const_node);
}

void TNodeVisitor::VisitDoubleCond(
    ast::DoubleCondExprNode* double_cond_expr_node) {
  Process(double_cond_expr_node);
  double_cond_expr_node->get_left_cond()->AcceptVisitor(this);
  double_cond_expr_node->get_right_cond()->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelExpr(ast::RelExprNode* rel_expr_node) {
  Process(rel_expr_node);
  rel_expr_node->get_left_factor()->AcceptVisitor(this);
  rel_expr_node->get_right_factor()->AcceptVisitor(this);
}

void TNodeVisitor::VisitRelFactor(ast::RelFactor* rel_factor) {
  Process(rel_factor);
  rel_factor->get_expr()->AcceptVisitor(this);
  rel_factor->get_ref()->AcceptVisitor(this);
}
}  // namespace sp
