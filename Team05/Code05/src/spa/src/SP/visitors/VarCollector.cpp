#include "VarCollector.h"

namespace sp {
void VarCollector::VisitVar(ast::VarNode* var_node) {
  vars.insert(var_node->get_name());
}
}  // namespace sp
