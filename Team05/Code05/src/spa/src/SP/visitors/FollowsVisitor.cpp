#include "FollowsVisitor.h"

namespace sp {
void FollowsVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void FollowsVisitor::VisitProc(ast::ProcNode* proc_node) {
  proc_node->get_children()->AcceptVisitor(this);
}

void FollowsVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  std::vector<std::unique_ptr<ast::StmtNode>>& stmts =
      stmtlst_node->get_children();

  for (int i = 0; i < stmts.size() - 1; i++) {
    pkb_ptr_->AddFollowsData(stmts[i]->get_line(), stmts[i + 1]->get_line());
  }

  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void FollowsVisitor::VisitIf(ast::IfNode* if_node) {
  if_node->get_then()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
}

void FollowsVisitor::VisitWhile(ast::WhileNode* while_node) {
  while_node->get_stmts()->AcceptVisitor(this);
}
}  // namespace sp
