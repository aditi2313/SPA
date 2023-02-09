#include "FactorNode.h"

#include "SP/visitors/TNodeVisitor.h"
#include "SP/visitors/ValidatorVisitor.h"

namespace ast {
void VarNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitVar(this);
}

void VarNode::AcceptVisitor(sp::ValidatorVisitor *visitor) {
  visitor->Visit(this);
}

void ConstNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitConst(this);
}

void ConstNode::AcceptVisitor(sp::ValidatorVisitor *visitor) {
    visitor->Visit(this);
}

void PlusNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitPlus(this);
}

void PlusNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void MinusNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitMinus(this);
}

void MinusNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void TimesNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitTimes(this);
}

void TimesNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void DivNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitDiv(this);
}

void DivNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void ModNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitMod(this);
}

void ModNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}
}  // namespace ast
