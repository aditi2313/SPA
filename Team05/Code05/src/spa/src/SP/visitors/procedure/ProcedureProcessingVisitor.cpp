#include "ProcedureProcessingVisitor.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "SP/utils/TopologicalSorter.h"
#include "SP/visitors/VarCollector.h"

namespace sp {

// Merges the variables used by a procedure directly with the variables used
// indirectly via calls within the procedure in topological order. Then writes
// the results to PKB.
void ProcedureProcessingVisitor::ProcessAft(ast::ProgramNode* program_node) {
  auto topological_order = sp::TopologicalSorter::Sort(called_by_);
  // Assert that all procedures are in the topological order vector
  for (auto& proc_nodes : program_node->get_children()) {
    assert(proc_calls_.count(proc_nodes->get_name()) == 0 ||
           std::find(topological_order.begin(), topological_order.end(),
                     proc_nodes->get_name()) != topological_order.end());
  }

  for (auto& proc : topological_order) {
    auto& merged_uses = direct_data_[proc];
    auto& l_calls = proc_called_by_line_[proc];
    for (auto& called_proc : proc_calls_[proc]) {
      merged_uses.merge(direct_data_[called_proc]);
    }
    for (auto& line : l_calls) {
      adding_function_(line, merged_uses);
      auto& calling_proc = call_to_proc_.at(line);
      auto tmp = merged_uses;
      direct_data_[calling_proc].merge(tmp);
    }

    adding_function_(proc, merged_uses);
    direct_data_.erase(proc);
  }

  for (auto& [proc, data] : direct_data_) {
    adding_function_(proc, data);
  }

  for (int i = containers_visited_.size() - 1; i >= 0; --i) {
    ast::ContainerNode* container = containers_visited_.at(i);
    std::unordered_set<std::string> vars;
    for (auto& stmt_node : container->get_total_stmts()) {
      AddVariablesFromStmtList(*stmt_node, vars);
    }
    adding_function_(container->get_line(), vars);
  }
}

void ProcedureProcessingVisitor::Process(ast::ProcNode* proc_node) {
  // Set the current procedure name so that we can insert variables
  // used directly by the procedure
  current_procedure_ = proc_node->get_name();
}

void ProcedureProcessingVisitor::Process(ast::CallNode* call_node) {
  auto parent_proc = call_node->get_parent_proc();
  auto called_proc = call_node->get_called_proc();
  called_by_[called_proc].insert(parent_proc);
  proc_calls_[parent_proc].insert(called_proc);
  proc_called_by_line_[called_proc].insert(call_node->get_line());
  call_to_proc_[call_node->get_line()] = parent_proc;
}

void ProcedureProcessingVisitor::Process(ast::WhileNode* while_node) {
  containers_visited_.push_back(while_node);
}

void ProcedureProcessingVisitor::Process(ast::IfNode* if_node) {
  containers_visited_.push_back(if_node);
}

}  // namespace sp
