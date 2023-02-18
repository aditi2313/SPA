#include "AssignVisitor.h"

namespace sp {

void AssignVisitor::VisitAssign(ast::AssignNode* assign_node) {
  pkb_ptr_->AddAssignData(assign_node->get_var()->get_name(),
                          assign_node->get_line(),
                          assign_node->get_expr()->Copy());
}

}  // namespace sp
