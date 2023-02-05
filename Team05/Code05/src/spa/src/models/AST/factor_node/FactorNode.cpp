#include "FactorNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void VarNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitVar(this);
}

void ConstNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitConst(this);
}

void PlusNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitPlus(this);
}

void MinusNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitMinus(this);
}

void TimesNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitTimes(this);
}

void DivNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitDiv(this);
}

void ModNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitMod(this);
}
}  // namespace ast