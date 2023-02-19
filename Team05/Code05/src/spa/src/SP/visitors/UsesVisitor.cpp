#include "UsesVisitor.h"

#include <unordered_set>

#include "SP/visitors/VarCollector.h"

namespace sp {

void UsesVisitor::Process(ast::AssignNode* assign_node) {
  VarCollector varCollector;
  assign_node->get_expr()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
}

void UsesVisitor::Process(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var()->get_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
}

void UsesVisitor::Process(ast::IfNode* if_node) {
  VarCollector varCollector;
  if_node->get_cond()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
}

void UsesVisitor::Process(ast::WhileNode* while_node) {
  VarCollector varCollector;
  while_node->get_cond()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
}

}  // namespace sp
