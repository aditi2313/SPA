#include <unordered_set>

#include "SP/visitors/ExpressionVisitor.h"
#include "UsesVisitor.h"

namespace sp {
void UsesVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void UsesVisitor::VisitProc(ast::ProcNode* proc_node) {
  proc_node->get_children()->AcceptVisitor(this);
}

void UsesVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void UsesVisitor::VisitAssign(ast::AssignNode* assign_node) {
  ExpressionVisitor exprVisitor;
  assign_node->get_expr()->AcceptVisitor(&exprVisitor);
  std::unordered_set<std::string> vars = exprVisitor.get_vars();
  pkb_ptr_->AddUsesData(assign_node->get_line(), vars);
}


void UsesVisitor::VisitPrint(ast::PrintNode* print_node) {
  std::unordered_set<std::string> vars = {print_node->get_var()->get_name()};
  pkb_ptr_->AddUsesData(print_node->get_line(), vars);
}


}  // namespace sp
