#include "ProgramNode.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void ProgramNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitProgram(this);
}
}  // namespace ast
