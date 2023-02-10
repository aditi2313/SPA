#include "StmtLstNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void StmtLstNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitStmtLst(this);
}
}  // namespace ast
