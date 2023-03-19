#include "DoubleCondExprNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void DoubleCondExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitDoubleCond(this);
}
}  // namespace ast
