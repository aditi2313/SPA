#include "SP/visitors/TNodeVisitor.h"

#include "AssignNode.h"

namespace ast {
void AssignNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitAssign(this);
}
}  // namespace ast
