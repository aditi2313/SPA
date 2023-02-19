#include "ModifiesVisitor.h"

#include <memory>
#include <utility>
#include <unordered_set>

namespace sp {

void ModifiesVisitor::Process(ast::AssignNode* assign_node) {
  std::unordered_set<std::string> vars = {assign_node->get_var()->get_name()};
  pkb_ptr_->AddModifiesData(assign_node->get_line(), vars);
}

void ModifiesVisitor::Process(ast::ReadNode* read_node) {
  std::unordered_set<std::string> vars = {read_node->get_var()->get_name()};
  pkb_ptr_->AddModifiesData(read_node->get_line(), vars);
}

void ModifiesVisitor::Process(ast::IfNode* if_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(if_node->get_else()), variables);
  AddVariablesFromStmtList(*(if_node->get_then()), variables);
  pkb_ptr_->AddModifiesData(if_node->get_line(), variables);
  
}

void ModifiesVisitor::Process(ast::WhileNode* while_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(while_node->get_stmts()), variables);
  pkb_ptr_->AddModifiesData(while_node->get_line(), variables);
}

}  // namespace sp
