#include "UsesVisitor.h"

#include <unordered_set>

#include "PKB/PKBRead.h"
#include "SP/visitors/VarCollector.h"
#include "common/filter/filters/IndexFilter.h"

namespace sp {

// Merges the variables used by a procedure directly with the variables used
// indirectly via calls within the procedure, then writes the results to PKB.
void UsesVisitor::ProcessAfter(ast::ProgramNode* program_node) {
  for (auto& proc_node : program_node->get_children()) {
    auto parent_proc = proc_node->get_name();
    auto parent_uses = proc_direct_uses_[parent_proc];
    for (auto& child_call : proc_calls_[parent_proc]) {
      auto child_uses = proc_direct_uses_[child_call];
      parent_uses.merge(child_uses);
      pkb_ptr_->AddUsesData(parent_proc, parent_uses);
    }
  }
}

// Collects the vars that the procedure uses directly
void UsesVisitor::Process(ast::ProcNode* proc_node) {
  VarCollector var_collector;
  proc_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();
  proc_direct_uses_.insert({proc_node->get_name(), vars});
}

void UsesVisitor::Process(ast::AssignNode* assign_node) {
  VarCollector var_collector;
  auto& expr_node = assign_node->get_expr();
  expr_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
}

void UsesVisitor::Process(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
}

void UsesVisitor::Process(ast::IfNode* if_node) {
  VarCollector var_collector;
  auto& cond_node = if_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the additional variables from the sub statement lists
  AddVariablesFromStmtList(*(if_node->get_then()), vars);
  AddVariablesFromStmtList(*(if_node->get_else()), vars);

  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
}

void UsesVisitor::Process(ast::WhileNode* while_node) {
  VarCollector var_collector;
  auto& cond_node = while_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the variables from the sub statements
  AddVariablesFromStmtList(*(while_node->get_stmts()), vars);
  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
}

void UsesVisitor::Process(ast::CallNode* call_node) {
  auto parent_proc = call_node->get_parent_proc();
  auto calls = proc_calls_[parent_proc];
  calls.insert(call_node->get_var()->get_name());
  proc_calls_[parent_proc] = calls;
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
    for (auto& var : variables) {
      vars.insert(var);
    }
  }
  pkb = reader.EndRead();
  pkb_ptr_ = std::make_unique<pkb::PKBWrite>(std::move(pkb));
}

}  // namespace sp
