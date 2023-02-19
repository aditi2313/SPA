#include "VarCollector.h"

namespace sp {
void VarCollector::PerformWork(ast::VarNode* var_node) {
  vars.insert(var_node->get_name());
}
}  // namespace sp
