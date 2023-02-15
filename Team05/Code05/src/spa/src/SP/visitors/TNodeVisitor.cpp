#include "SP/visitors/TNodeVisitor.h"

namespace sp {
void TNodeVisitor::VisitIf(ast::IfNode* if_node) {
  if_node->get_cond()->AcceptVisitor(this);
  if_node->get_then()->AcceptVisitor(this);
  if_node->get_else()->AcceptVisitor(this);
}

void TNodeVisitor::VisitWhile(ast::WhileNode* while_node) {
  while_node->get_cond()->AcceptVisitor(this);
  while_node->get_stmts()->AcceptVisitor(this);
}
}  // namespace sp