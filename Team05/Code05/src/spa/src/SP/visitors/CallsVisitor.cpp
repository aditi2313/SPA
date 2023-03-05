#include "CallsVisitor.h"

namespace sp {

void sp::CallsVisitor::Process(ast::CallNode *call_node) {
  pkb_ptr_->AddCallsData(call_node->get_parent_proc(),
                         call_node->get_var()->get_name());
}

}  // namespace sp
