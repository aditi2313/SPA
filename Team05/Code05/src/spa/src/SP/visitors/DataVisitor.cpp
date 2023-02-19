#include "DataVisitor.h"

namespace sp {

void DataVisitor::Process(ast::ProcNode* proc_node) {
  pkb_ptr_->add_procedure(proc_node->get_name());
}

void DataVisitor::Process(ast::AssignNode* assign_node) {
  pkb_ptr_->add_stmt(assign_node->get_line());
  pkb_ptr_->add_assign(assign_node->get_line());
  assign_node->get_expr()->AcceptVisitor(this);
  assign_node->get_var()->AcceptVisitor(this);
}
void DataVisitor::Process(ast::ReadNode* read_node) {
  pkb_ptr_->add_variable(read_node->get_var()->get_name());
  pkb_ptr_->add_read(read_node->get_line());
  pkb_ptr_->add_stmt(read_node->get_line());
}
void DataVisitor::Process(ast::PrintNode* print_node) {
  pkb_ptr_->add_stmt(print_node->get_line());
  pkb_ptr_->add_print(print_node->get_line());
}

void DataVisitor::Process(ast::CallNode* call_node) {
  pkb_ptr_->add_call(call_node->get_line());
  pkb_ptr_->add_stmt(call_node->get_line());
}
void DataVisitor::Process(ast::VarNode* var_node) {
  pkb_ptr_->add_variable(var_node->get_name());
}
void DataVisitor::Process(ast::ConstNode* const_node) {
  pkb_ptr_->add_constant(const_node->get_val());
}

void DataVisitor::Process(ast::WhileNode* while_node) {
  pkb_ptr_->add_while(while_node->get_line());
  pkb_ptr_->add_stmt(while_node->get_line());
}

void DataVisitor::Process(ast::IfNode* if_node) {
  pkb_ptr_->add_if(if_node->get_line());
  pkb_ptr_->add_stmt(if_node->get_line());
}

}  // namespace sp
