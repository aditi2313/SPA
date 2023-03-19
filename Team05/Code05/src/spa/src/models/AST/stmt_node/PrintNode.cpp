#include "SP/visitors/TNodeVisitor.h"

#include "PrintNode.h"

namespace ast {
void PrintNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitPrint(this);
}
}  // namespace ast
