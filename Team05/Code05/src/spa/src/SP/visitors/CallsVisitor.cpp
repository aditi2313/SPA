#include "CallsVisitor.h"

namespace sp {

void sp::CallsVisitor::Process(ast::CallNode *call_node) {
  auto &var = call_node->get_var();
  auto callee_name = var->get_name();
  pkb_ptr_->AddCallsData(call_node->get_parent_proc(),
                         callee_name);
  pkb_ptr_->AddWithData(call_node->get_line(), callee_name);
}

}  // namespace sp
