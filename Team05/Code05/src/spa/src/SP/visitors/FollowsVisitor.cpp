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
  std::vector<std::unique_ptr<ast::StmtNode>> stmts =
      stmtlst_node->get_children();
  for (int i = 0; i < stmts.size(); i++) {
    pkb_ptr_->AddFollowsData(stmts[i]->get_line(), stmts[i + 1]->get_line());
  }
}
}  // namespace sp