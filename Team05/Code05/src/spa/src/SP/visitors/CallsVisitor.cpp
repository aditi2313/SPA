#include "CallsVisitor.h"

namespace sp {

void sp::CallsVisitor::Process(ast::CallNode *call_node) {
  auto &var = call_node->get_called_proc();
  auto callee_name = call_node->get_called_proc();
  pkb_ptr_->AddCallsData(call_node->get_parent_proc(),
                         callee_name);
  pkb_ptr_->set_proc_name_for_line(call_node->get_line(), callee_name);
}

}  // namespace sp
