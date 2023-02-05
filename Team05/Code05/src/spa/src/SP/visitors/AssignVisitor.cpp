#pragma once

#include "AssignVisitor.h"

namespace sp {
void AssignVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void AssignVisitor::VisitProc(ast::ProcNode* proc_node) {
  proc_node->get_children()->AcceptVisitor(this);
}

void AssignVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void AssignVisitor::VisitAssign(ast::AssignNode* assign_node) {
  pkb_ptr_->AddAssignData(assign_node->get_var()->get_name(), assign_node->get_line(),
                          assign_node->get_expr()->Copy());
}
}  // namespace sp