#include "StmtNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {

void AssignNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitAssign(this);
}

void ReadNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRead(this);
}

void PrintNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitPrint(this);
}

void CallNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitCall(this);
}
}  // namespace ast
