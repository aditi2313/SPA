#include "AssignVisitor.h"

namespace sp {

void AssignVisitor::Process(ast::AssignNode *assign_node) {
  pkb_ptr_->AddAssignData(assign_node->get_var_name(),
                          assign_node->get_line(),
                          assign_node->get_expr_copy());
}

}  // namespace sp
