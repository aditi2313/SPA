#include "CallValidator.h"
#include "SP/utils/TopologicalSorter.h"
#include "common/exceptions/SPExceptions.h"

namespace sp {
void CallValidator::Validate() {
  ValidateProcedureNameExists();
  ValidateNoCyclicCalls();
}

void CallValidator::ValidateProcedureNameExists() {
  for (auto &call_name : call_names_set_) {
    if (!procedure_names_set_.count(call_name)) {
      throw CallSemanticsException("procedure does not exist: " + call_name);
    }
  }
}

void CallValidator::ValidateNoCyclicCalls() {
  // Topological ordering does not exist iff there is a directed cycle
  if (sp::TopologicalSorter::Sort(called_by_).size() != called_by_.size()) {
    throw CallSemanticsException("cyclic call detected");
  }
}

void CallValidator::Accept(ast::ProcNode &proc_node) {
  procedure_names_set_.insert(proc_node.get_name());
}

void CallValidator::Accept(ast::CallNode &call_node) {
  auto called_proc = call_node.get_var()->get_name();
  call_names_set_.insert(called_proc);
  called_by_[called_proc].insert(call_node.get_parent_proc());
}
}  // namespace sp
