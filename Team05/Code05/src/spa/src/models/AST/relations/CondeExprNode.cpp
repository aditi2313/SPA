#include "CondExprNode.h"
#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void DoubleCondExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitDoubleCond(this);
}

void NotExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitNot(this);
}

}  // namespace ast