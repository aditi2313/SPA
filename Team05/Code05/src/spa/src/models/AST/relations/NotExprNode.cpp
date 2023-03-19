#include "NotExprNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void NotExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitNot(this);
}
}  // namespace ast
