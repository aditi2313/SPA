#include "FactorNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void VarNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitVar(this);
}

void ConstNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitConst(this);
}

void OpNode::AcceptVisitor(sp::TNodeVisitor* visitor) {}
}  // namespace ast
