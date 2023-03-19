#include "SP/visitors/TNodeVisitor.h"

#include "CallNode.h"

namespace ast {
void CallNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitCall(this);
}
}  // namespace ast
