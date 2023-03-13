#include "UsesVisitor.h"

#include <unordered_set>

#include "PKB/PKBRead.h"
#include "SP/utils/TopologicalSorter.h"
#include "SP/visitors/VarCollector.h"
#include "common/filter/filters/IndexFilter.h"

namespace sp {

// Merges the variables used by a procedure directly with the variables used
// indirectly via calls within the procedure in topological order. Then writes
// the results to PKB.
void UsesVisitor::ProcessAfter(ast::ProgramNode* program_node) {
  auto topological_order = sp::TopologicalSorter::Sort(called_by_);
  // Assert that all procedures are in the topological order vector
  for (auto& proc_nodes : program_node->get_children()) {
    assert(proc_calls_.count(proc_nodes->get_name()) == 0 ||
           std::find(topological_order.begin(), topological_order.end(),
                     proc_nodes->get_name()) != topological_order.end());
  }

  for (auto& proc : topological_order) {
    auto& merged_uses = direct_uses_[proc];
    for (auto& called_proc : proc_calls_[proc]) {
      merged_uses.merge(direct_uses_[called_proc]);
    }
    pkb_ptr_->AddUsesData(proc, merged_uses);
    direct_uses_.erase(proc);
  }

  for (auto& [proc, data] : direct_uses_) {
    pkb_ptr_->AddUsesData(proc, data);
  }
}

void UsesVisitor::Process(ast::ProcNode* proc_node) {
  // Set the current procedure name so that we can insert variables
  // used directly by the procedure
  current_procedure_ = proc_node->get_name();
}

void UsesVisitor::Process(ast::AssignNode* assign_node) {
  VarCollector var_collector;
  auto& expr_node = assign_node->get_expr();
  expr_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
  direct_uses_[current_procedure_].merge(vars);
}

void UsesVisitor::Process(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
  direct_uses_[current_procedure_].merge(vars);
}

void UsesVisitor::ProcessAft(ast::IfNode* if_node) {
  VarCollector var_collector;
  auto& cond_node = if_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the additional variables from the sub statement lists
  AddVariablesFromStmtList(*(if_node->get_then()), vars);
  AddVariablesFromStmtList(*(if_node->get_else()), vars);

  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
  direct_uses_[current_procedure_].merge(vars);
}

void UsesVisitor::ProcessAft(ast::WhileNode* while_node) {
  VarCollector var_collector;
  auto& cond_node = while_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the variables from the sub statements
  AddVariablesFromStmtList(*(while_node->get_stmts()), vars);
  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
  direct_uses_[current_procedure_].merge(vars);
}

void UsesVisitor::Process(ast::CallNode* call_node) {
  auto parent_proc = call_node->get_parent_proc();
  auto called_proc = call_node->get_var()->get_name();
  called_by_[called_proc].insert(parent_proc);
  proc_calls_[parent_proc].insert(called_proc);
}

void UsesVisitor::AddVariablesFromStmtList(
    ast::StmtLstNode& node, std::unordered_set<std::string>& vars) {
  auto pkb = pkb_ptr_->EndWrite();
  pkb::PKBRead reader(std::move(pkb));
  for (auto& child : node.get_children()) {
    auto result =
        reader
            .Uses(std::make_unique<filter::UsesIndexFilter>(child->get_line()))
            ->get_result();
    if (result->empty()) continue;
    auto variables = result->get_row(child->get_line()).get_variables();
    vars.merge(variables);
  }
  pkb = reader.EndRead();
  pkb_ptr_ = std::make_unique<pkb::PKBWrite>(std::move(pkb));
}

}  // namespace sp
