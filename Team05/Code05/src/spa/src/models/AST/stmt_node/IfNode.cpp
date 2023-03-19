#include "SP/visitors/TNodeVisitor.h"

#include "IfNode.h"

namespace ast {
void IfNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitIf(this);
}
}  // namespace ast
