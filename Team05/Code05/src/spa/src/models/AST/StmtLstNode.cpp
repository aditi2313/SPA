#include "StmtLstNode.h"

#include "SP/visitors/TNodeVisitor.h"
#include "SP/visitors/ValidatorVisitor.h"

namespace ast {
void StmtLstNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitStmtLst(this);
}
void StmtLstNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}
}  // namespace ast
