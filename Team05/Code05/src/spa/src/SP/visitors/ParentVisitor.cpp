#include "ParentVisitor.h"

namespace sp {

void ParentVisitor::PerformWork(ast::IfNode *if_node) {
  auto parent_line = if_node->get_line();
  for (auto &stmt_node : if_node->get_then()->get_children()) {
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
  for (auto &stmt_node : if_node->get_else()->get_children()) {
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
}

void ParentVisitor::PerformWork(ast::WhileNode *while_node) {
  auto parent_line = while_node->get_line();
  for (auto &stmt_node : while_node->get_stmts()->get_children()) {
    pkb_ptr_->AddParentData(stmt_node->get_line(), parent_line);
  }
}

}  // namespace sp
