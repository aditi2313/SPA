#include "StmtNode.h"

#include "SP/visitors/TNodeVisitor.h"
#include "SP/visitors/ValidatorVisitor.h"

namespace ast {

void AssignNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitAssign(this);
}
void AssignNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void ReadNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRead(this);
}
void ReadNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void PrintNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitPrint(this);
}
void PrintNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

void CallNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitCall(this);
}
void CallNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}

}  // namespace ast
