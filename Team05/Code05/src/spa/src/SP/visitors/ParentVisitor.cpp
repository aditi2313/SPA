#include "ParentVisitor.h"

namespace sp {

void ParentVisitor::Process(ast::IfNode *if_node) {
  auto parent_line = if_node->get_line();

  auto& then_stmt_lst = if_node->get_then();
  for (auto &stmt_node : then_stmt_lst->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }

  auto& else_stmt_lst = if_node->get_else();
  for (auto &stmt_node : else_stmt_lst->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }
}

void ParentVisitor::Process(ast::WhileNode *while_node) {
  auto parent_line = while_node->get_line();

  auto& stmt_lst = while_node->get_stmts();
  for (auto &stmt_node : stmt_lst->get_children()) {
    pkb_ptr_->AddParentData(parent_line, stmt_node->get_line());
  }
}

}  // namespace sp
