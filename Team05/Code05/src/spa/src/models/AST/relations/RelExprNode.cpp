#include "RelExprNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void RelExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRelExpr(this);
}

void RelFactor::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRelFactor(this);
}

}  // namespace ast
