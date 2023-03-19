#include "SP/visitors/TNodeVisitor.h"

#include "ReadNode.h"

namespace ast {
void ReadNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRead(this);
}
}  // namespace ast
