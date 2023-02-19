#include "ParentVisitor.h"

namespace sp {

void ParentVisitor::Process(ast::IfNode *if_node) {
  auto parent_line = if_node->get_line();
  for (auto &stmt_node : if_node->get_then()->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }
  for (auto &stmt_node : if_node->get_else()->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }
}

void ParentVisitor::Process(ast::WhileNode *while_node) {
  auto parent_line = while_node->get_line();
  for (auto &stmt_node : while_node->get_stmts()->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }
}

}  // namespace sp
