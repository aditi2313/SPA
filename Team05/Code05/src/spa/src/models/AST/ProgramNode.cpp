#include "ProgramNode.h"

#include "SP/visitors/TNodeVisitor.h"
#include "SP/validators/ValidatorVisitor.h"

namespace ast {
void ProgramNode::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitProgram(this);
}

void ProgramNode::AcceptVisitor(sp::ValidatorVisitor* visitor) {
  visitor->Visit(this);
}
}  // namespace ast
