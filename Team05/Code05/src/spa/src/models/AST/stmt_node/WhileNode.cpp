#include "SP/visitors/TNodeVisitor.h"

#include "WhileNode.h"

namespace ast {
void WhileNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitWhile(this);
}
}  // namespace ast
