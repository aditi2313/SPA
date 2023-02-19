#include "DataVisitor.h"

namespace sp {

void DataVisitor::PerformWork(ast::ProcNode* proc_node) {
  pkb_ptr_->add_procedure(proc_node->get_name());
}

void DataVisitor::PerformWork(ast::AssignNode* assign_node) {
  pkb_ptr_->add_stmt(assign_node->get_line());
  pkb_ptr_->add_assign(assign_node->get_line());
}
void DataVisitor::PerformWork(ast::ReadNode* read_node) {
  pkb_ptr_->add_variable(read_node->get_var()->get_name());
  pkb_ptr_->add_read(read_node->get_line());
  pkb_ptr_->add_stmt(read_node->get_line());
}
void DataVisitor::PerformWork(ast::PrintNode* print_node) {
  pkb_ptr_->add_stmt(print_node->get_line());
  pkb_ptr_->add_print(print_node->get_line());
}

void DataVisitor::PerformWork(ast::CallNode* call_node) {
  pkb_ptr_->add_call(call_node->get_line());
  pkb_ptr_->add_stmt(call_node->get_line());
}
void DataVisitor::PerformWork(ast::VarNode* var_node) {
  pkb_ptr_->add_variable(var_node->get_name());
}
void DataVisitor::PerformWork(ast::ConstNode* const_node) {
  pkb_ptr_->add_constant(const_node->get_val());
}

void DataVisitor::VisitWhile(ast::WhileNode* while_node) {
  pkb_ptr_->add_while(while_node->get_line());
  pkb_ptr_->add_stmt(while_node->get_line());
  while_node->get_cond()->AcceptVisitor(this);
  while_node->get_stmts()->AcceptVisitor(this);
}

void DataVisitor::VisitIf(ast::IfNode* if_node) {
  pkb_ptr_->add_if(if_node->get_line());
  pkb_ptr_->add_stmt(if_node->get_line());
  if_node->get_cond()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
}

}  // namespace sp
