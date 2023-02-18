#include "ParentVisitor.h"

namespace sp {

void ParentVisitor::VisitProc(ast::ProcNode *proc_node) {
  proc_node->get_children()->AcceptVisitor(this);
}

void ParentVisitor::VisitStmtLst(ast::StmtLstNode *stmtlst_node) {
  for (auto &stmt_node : stmtlst_node->get_children()) {
    stmt_node->AcceptVisitor(this);
  }
}

void ParentVisitor::VisitIf(ast::IfNode *if_node) {
  auto parent_line = if_node->get_line();
  for (auto &stmt_node : if_node->get_then()->get_children()) {
    stmt_node->AcceptVisitor(this);
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
  for (auto &stmt_node : if_node->get_else()->get_children()) {
    stmt_node->AcceptVisitor(this);
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
}

void ParentVisitor::VisitWhile(ast::WhileNode *while_node) {
  auto parent_line = while_node->get_line();
  for (auto &stmt_node : while_node->get_stmts()->get_children()) {
    stmt_node->AcceptVisitor(this);
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
}

}  // namespace sp
