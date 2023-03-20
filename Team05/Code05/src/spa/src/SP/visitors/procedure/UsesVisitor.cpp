#include "UsesVisitor.h"

#include <unordered_set>

#include "PKB/PKBRead.h"
#include "SP/utils/TopologicalSorter.h"
#include "SP/visitors/VarCollector.h"
#include "common/filter/filters/IndexFilter.h"

namespace sp {

void UsesVisitor::Process(ast::AssignNode* assign_node) {
  VarCollector var_collector;
  auto& expr_node = assign_node->get_expr();
  expr_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
  direct_data_[current_procedure_].merge(vars);
}

void UsesVisitor::Process(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
  direct_data_[current_procedure_].merge(vars);
  pkb_ptr_->set_var_name_for_line(print_node->get_line(),
                                  print_node->get_var_name());
}

void UsesVisitor::ProcessAft(ast::IfNode* if_node) {
  VarCollector var_collector;
  auto& cond_node = if_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> cond_vars = var_collector.get_vars();
  std::unordered_set<std::string> vars(cond_vars);

  // add the additional variables from the sub statement lists
  AddVariablesFromStmtList(*(if_node->get_then()), vars);
  AddVariablesFromStmtList(*(if_node->get_else()), vars);

  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
  pkb_ptr_->AddConditionData(if_node->get_line(), cond_vars);

  direct_data_[current_procedure_].merge(vars);
}

void UsesVisitor::ProcessAft(ast::WhileNode* while_node) {
  VarCollector var_collector;
  auto& cond_node = while_node->get_cond();
  cond_node->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> cond_vars = var_collector.get_vars();
  std::unordered_set<std::string> vars(cond_vars);

  // add the variables from the sub statements
  AddVariablesFromStmtList(*(while_node->get_stmts()), vars);
  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
  pkb_ptr_->AddConditionData(while_node->get_line(), cond_vars);

  direct_data_[current_procedure_].merge(vars);
}

void UsesVisitor::AddVariablesFromStmtList(
    ast::StmtLstNode& node, std::unordered_set<std::string>& vars) {
  auto pkb = pkb_ptr_->EndWrite();
  pkb::PKBRead reader(std::move(pkb));
  for (auto& child : node.get_children()) {
    auto table = reader
            .Uses(std::make_unique<filter::UsesIndexFilter>(child->get_line()));
    auto result = table->get_result();
    if (result->empty()) continue;
    auto& uses_data = result->get_row(child->get_line());
    auto variables = uses_data.get_variables();
    vars.merge(variables);
  }
  pkb = reader.EndRead();
  pkb_ptr_ = std::make_unique<pkb::PKBWrite>(std::move(pkb));
}

}  // namespace sp
