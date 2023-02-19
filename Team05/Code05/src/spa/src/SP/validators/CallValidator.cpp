#include "CallValidator.h"
#include "common/exceptions/SPExceptions.h"

namespace sp {
bool CallValidator::Validate() {
  return ValidateProcedureNameExists();
}

bool CallValidator::ValidateProcedureNameExists() {
  for (auto &call_name : call_names_set) {
    if (!procedure_names_set_.count(call_name)) {
      throw CallSemanticsException("procedure does not exist: " + call_name);
    }
  }

  return true;
}

void CallValidator::Accept(ast::ProcNode &proc_node) {
  procedure_names_set_.insert(proc_node.get_name());
}

void CallValidator::Accept(ast::CallNode &call_node) {
  call_names_set.insert(call_node.get_var()->get_name());
}
}  // namespace sp
