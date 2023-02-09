#include "ProcNode.h"

#include "SP/visitors/TNodeVisitor.h"
#include "SP/visitors/ValidatorVisitor.h"

namespace ast {
void ProcNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitProc(this);
}

void ProcNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}
}  // namespace ast
