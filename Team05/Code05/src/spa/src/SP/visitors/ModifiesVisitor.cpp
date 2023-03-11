#include "ModifiesVisitor.h"

#include "SP/utils/TopologicalSorter.h"

namespace sp {

// Merges the variables modified by a procedure directly with the variables
// modified indirectly via calls within the procedure in topological order.
// Then writes the results to PKB.
void ModifiesVisitor::ProcessAft(ast::ProgramNode* program_node) {
  auto topological_order = sp::TopologicalSorter::Sort(called_by_);
  // Assert that all procedures are in the topological order vector
  for (auto& proc_nodes : program_node->get_children()) {
    assert(proc_calls_.count(proc_nodes->get_name()) == 0 ||
           std::find(topological_order.begin(), topological_order.end(),
                     proc_nodes->get_name()) != topological_order.end());
  }

  for (auto& proc : topological_order) {
    auto& merged_modifies = direct_modifies_[proc];
    for (auto& called_proc : proc_calls_[proc]) {
      merged_modifies.merge(direct_modifies_[called_proc]);
    }
    pkb_ptr_->AddModifiesData(proc, merged_modifies);
  }
}

void ModifiesVisitor::Process(ast::ProcNode* proc_node) {
  // Set the current procedure name so that we can insert variables
  // used directly by the procedure
  current_procedure_ = proc_node->get_name();
}

void ModifiesVisitor::Process(ast::AssignNode* assign_node) {
  std::unordered_set<std::string> vars = {assign_node->get_var_name()};
  pkb_ptr_->AddModifiesData(assign_node->get_line(), vars);
  direct_modifies_[current_procedure_].merge(vars);
}

void ModifiesVisitor::Process(ast::ReadNode* read_node) {
  std::unordered_set<std::string> vars = {read_node->get_var_name()};
  pkb_ptr_->AddModifiesData(read_node->get_line(), vars);
  direct_modifies_[current_procedure_].merge(vars);
}

void ModifiesVisitor::ProcessAft(ast::IfNode* if_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(if_node->get_else()), variables);
  AddVariablesFromStmtList(*(if_node->get_then()), variables);
  pkb_ptr_->AddModifiesData(if_node->get_line(), variables);
  direct_modifies_[current_procedure_].merge(variables);
}

void ModifiesVisitor::ProcessAft(ast::WhileNode* while_node) {
  std::unordered_set<std::string> variables;
  AddVariablesFromStmtList(*(while_node->get_stmts()), variables);
  pkb_ptr_->AddModifiesData(while_node->get_line(), variables);
  direct_modifies_[current_procedure_].merge(variables);
}

void ModifiesVisitor::Process(ast::CallNode* call_node) {
  auto parent_proc = call_node->get_parent_proc();
  auto called_proc = call_node->get_var()->get_name();
  called_by_[called_proc].insert(parent_proc);
  proc_calls_[parent_proc].insert(called_proc);
}

}  // namespace sp
