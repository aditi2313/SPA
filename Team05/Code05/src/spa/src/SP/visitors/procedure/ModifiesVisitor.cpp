#include "ModifiesVisitor.h"

#include "SP/utils/TopologicalSorter.h"

namespace sp {

void ModifiesVisitor::Process(ast::AssignNode* assign_node) {
  std::unordered_set<std::string> vars = {assign_node->get_var_name()};
  pkb_ptr_->AddModifiesData(assign_node->get_line(), vars);
  direct_data_[current_procedure_].merge(vars);
}

void ModifiesVisitor::Process(ast::ReadNode* read_node) {
  std::unordered_set<std::string> vars = {read_node->get_var_name()};
  pkb_ptr_->AddModifiesData(read_node->get_line(), vars);
  direct_data_[current_procedure_].merge(vars);
  pkb_ptr_->set_var_name_for_line(read_node->get_line(),
                                  read_node->get_var_name());
}

void ModifiesVisitor::ProcessAft(ast::IfNode* if_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(if_node->get_else()), variables);
  AddVariablesFromStmtList(*(if_node->get_then()), variables);
  pkb_ptr_->AddModifiesData(if_node->get_line(), variables);
  direct_data_[current_procedure_].merge(variables);
}

void ModifiesVisitor::ProcessAft(ast::WhileNode* while_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(while_node->get_stmts()), variables);
  pkb_ptr_->AddModifiesData(while_node->get_line(), variables);
  direct_data_[current_procedure_].merge(variables);
}

}  // namespace sp
