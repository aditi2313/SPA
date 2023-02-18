#include "SP/visitors/TNodeVisitor.h"

namespace sp {

void TNodeVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void TNodeVisitor::VisitIf(ast::IfNode* if_node) {
  if_node->get_cond()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
}

void TNodeVisitor::VisitWhile(ast::WhileNode* while_node) {
  while_node->get_cond()->AcceptVisitor(this);
  while_node->get_stmts()->AcceptVisitor(this);
}

void TNodeVisitor::VisitOpNode(ast::OpNode* op_node) {
  op_node->get_left()->AcceptVisitor(this);
  op_node->get_right()->AcceptVisitor(this);
}
}  // namespace sp
