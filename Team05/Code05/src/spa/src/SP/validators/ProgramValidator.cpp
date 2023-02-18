#include "ProgramValidator.h"
#include "CallValidator.h"
#include "ProcedureValidator.h"

namespace sp {
bool ProgramValidator::Validate() {
  // Traverse tree to get required info
  root_->AcceptVisitor(this);
  return procedure_validator_.Validate() && call_validator_.Validate();
}

void ProgramValidator::VisitProc(ast::ProcNode *proc_node) {
  procedure_validator_.Accept(*proc_node);
  call_validator_.Accept(*proc_node);

  proc_node->get_children()->AcceptVisitor(this);
}

void ProgramValidator::VisitStmtLst(ast::StmtLstNode *stmtlst_node) {
  for (auto &stmt_node : stmtlst_node->get_children()) {
    stmt_node->AcceptVisitor(this);
  }
}

void ProgramValidator::VisitCall(ast::CallNode *call_node) {
  call_validator_.Accept(*call_node);
}

}  // namespace sp
