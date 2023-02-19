#include "ProgramValidator.h"
#include "CallValidator.h"
#include "ProcedureValidator.h"

namespace sp {
bool ProgramValidator::Validate() {
  // Traverse tree to get required info
  root_->AcceptVisitor(this);
  return procedure_validator_.Validate() && call_validator_.Validate();
}

void ProgramValidator::Process(ast::ProcNode *proc_node) {
  procedure_validator_.Accept(*proc_node);
  call_validator_.Accept(*proc_node);
}

void ProgramValidator::Process(ast::CallNode *call_node) {
  call_validator_.Accept(*call_node);
}

}  // namespace sp
