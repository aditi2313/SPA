#include "UsesVisitor.h"

#include <unordered_set>

#include "PKB/PKBRead.h"
#include "SP/visitors/VarCollector.h"
#include "common/filter/filters/IndexFilter.h"

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
  VarCollector var_collector;
  if_node->get_cond()->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the additional variables from the sub statement lists
  auto pkb = pkb_ptr_->EndWrite();
  auto pkb_read = pkb::PKBRead(std::move(pkb));
  AddVariablesFromStmtList(pkb_read, *if_node->get_then(), vars);
  AddVariablesFromStmtList(pkb_read, *if_node->get_else(), vars);
  pkb_ptr_ = std::make_unique<pkb::PKBWrite>(pkb_read.EndRead());

  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
}

void UsesVisitor::Process(ast::WhileNode* while_node) {
  VarCollector var_collector;
  while_node->get_cond()->AcceptVisitor(&var_collector);
  std::unordered_set<std::string> vars = var_collector.get_vars();

  // add the variables from the sub statements
  auto pkb = pkb_ptr_->EndWrite();
  auto pkb_read = pkb::PKBRead(std::move(pkb));
  AddVariablesFromStmtList(pkb_read, *while_node->get_stmts(), vars);
  pkb_ptr_ = std::make_unique<pkb::PKBWrite>(pkb_read.EndRead());

  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
}

void UsesVisitor::AddVariablesFromStmtList(
    pkb::PKBRead& pkb_read, ast::StmtLstNode& node,
    std::unordered_set<std::string>& vars) {
  for (auto& child : node.get_children()) {
    auto result =
        pkb_read
            .Uses(std::make_unique<filter::UsesIndexFilter>(child->get_line()))
            ->get_result();
    if (result->empty()) continue;
    auto variables = result->get_row(child->get_line()).get_variables();
    for (auto& var : variables) {
      vars.insert(var);
    }
  }
}

}  // namespace sp
