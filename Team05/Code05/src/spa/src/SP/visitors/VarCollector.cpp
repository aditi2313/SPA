#include "VarCollector.h"

namespace sp {
void VarCollector::Process(ast::VarNode* var_node) {
  vars.insert(var_node->get_name());
}
}  // namespace sp
