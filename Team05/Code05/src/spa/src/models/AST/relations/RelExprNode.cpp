#include "RelExprNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void RelExprNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRelExpr(this);
}
}  // namespace ast
