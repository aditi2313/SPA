#include "RelFactor.h"

#include "SP/visitors/TNodeVisitor.h"

namespace ast {
void RelFactor::AcceptVisitor(sp::TNodeVisitor* visitor) {
  visitor->VisitRelFactor(this);
}
}  // namespace ast
