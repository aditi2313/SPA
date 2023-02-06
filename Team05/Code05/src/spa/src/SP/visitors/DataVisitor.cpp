#include "DataVisitor.h"

namespace sp {

void DataVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
  int n;
}
void DataVisitor::VisitProc(ast::ProcNode* proc_node) {
  pkb_ptr_->add_procedure(proc_node->get_name());
  proc_node->get_children()->AcceptVisitor(this);
}
void DataVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void DataVisitor::VisitAssign(ast::AssignNode* assign_node) {
  pkb_ptr_->add_stmt(assign_node->get_line());
  pkb_ptr_->add_assign(assign_node->get_line());
}
void DataVisitor::VisitRead(ast::ReadNode* read_node) {
  pkb_ptr_->add_variable(read_node->get_var()->get_name());
  pkb_ptr_->add_read(read_node->get_line());
  pkb_ptr_->add_stmt(read_node->get_line());
}
void DataVisitor::VisitPrint(ast::PrintNode* print_node) {
  pkb_ptr_->add_stmt(print_node->get_line());
  pkb_ptr_->add_print(print_node->get_line());
}

void DataVisitor::VisitCall(ast::CallNode* call_node) {
  pkb_ptr_->add_calls(call_node->get_line());
  pkb_ptr_->add_stmt(call_node->get_line());
}
void DataVisitor::VisitFactor(ast::FactorNode* factor_node) {}
void DataVisitor::VisitExpr(ast::ExprNode* expr_node) {}
void DataVisitor::VisitTerm(ast::TermNode* term_node) {}
void DataVisitor::VisitVar(ast::VarNode* var_node) {
  pkb_ptr_->add_variable(var_node->get_name());
}
void DataVisitor::VisitConst(ast::ConstNode* const_node) {
  pkb_ptr_->add_constant(const_node->get_val());
}
void DataVisitor::VisitPlus(ast::PlusNode* plus_node) {
  plus_node->get_expr()->AcceptVisitor(this);
  plus_node->get_term()->AcceptVisitor(this);
}
void DataVisitor::VisitMinus(ast::MinusNode* node) {
  node->get_expr()->AcceptVisitor(this);
  node->get_term()->AcceptVisitor(this);
}
void DataVisitor::VisitTimes(ast::TimesNode* node) {
  node->get_factor()->AcceptVisitor(this);
  node->get_term()->AcceptVisitor(this);
}
void DataVisitor::VisitDiv(ast::DivNode* node) {
  node->get_factor()->AcceptVisitor(this);
  node->get_term()->AcceptVisitor(this);
}
void DataVisitor::VisitMod(ast::ModNode* node) {
  node->get_factor()->AcceptVisitor(this);
  node->get_term()->AcceptVisitor(this);
}

}  // namespace sp