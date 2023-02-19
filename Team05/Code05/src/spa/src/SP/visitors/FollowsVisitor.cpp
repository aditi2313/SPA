#include "FollowsVisitor.h"

namespace sp {

void FollowsVisitor::PerformWork(ast::StmtLstNode* stmtlst_node) {
  std::vector<std::unique_ptr<ast::StmtNode>>& stmts =
      stmtlst_node->get_children();
  for (int i = 0; i < stmts.size() - 1; i++) {
    pkb_ptr_->AddFollowsData(stmts[i]->get_line(), stmts[i + 1]->get_line());
  }
}

void FollowsVisitor::VisitWhile(ast::WhileNode* while_node) {
  while_node->get_stmts()->AcceptVisitor(this);
}
}  // namespace sp
