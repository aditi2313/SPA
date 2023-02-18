#include "UsesVisitor.h"

#include <unordered_set>

#include "SP/visitors/VarCollector.h"

namespace sp {

void UsesVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void UsesVisitor::VisitAssign(ast::AssignNode* assign_node) {
  VarCollector varCollector;
  assign_node->get_expr()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
}

void UsesVisitor::VisitPrint(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var()->get_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
}

void UsesVisitor::VisitIf(ast::IfNode* if_node) {
  if_node->get_else()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
  VarCollector varCollector;
  if_node->get_cond()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(if_node->get_line(), vars);
}

void UsesVisitor::VisitWhile(ast::WhileNode* while_node) {
  while_node->get_stmts()->AcceptVisitor(this);
  VarCollector varCollector;
  while_node->get_cond()->AcceptVisitor(&varCollector);
  std::unordered_set<std::string> vars = varCollector.get_vars();
  pkb_ptr_->AddUsesData(while_node->get_line(), vars);
}

}  // namespace sp
