#include "ProcNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void ProcNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitProc(this);
}
}  // namespace ast
