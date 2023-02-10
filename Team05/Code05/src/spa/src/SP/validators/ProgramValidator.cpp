#include "ProgramValidator.h"
#include "CallValidator.h"
#include "ProcedureValidator.h"

namespace sp {
bool ProgramValidator::Validate() {
  // Traverse tree to get required info
  root_->AcceptVisitor(this);
  auto procedure_validator = sp::ProcedureValidator(procedure_names_);
  auto call_validator = sp::CallValidator(procedure_names_, call_names_);
  return procedure_validator.Validate() && call_validator.Validate();
}

void ProgramValidator::VisitProgram(ast::ProgramNode *program_node) {
  for (auto &proc_node : program_node->get_children()) {
    proc_node->AcceptVisitor(this);
  }
}

void ProgramValidator::VisitProc(ast::ProcNode *proc_node) {
  auto proc_name = proc_node->get_name();
  procedure_names_.push_back(proc_name);

  proc_node->get_children()->AcceptVisitor(this);
}

void ProgramValidator::VisitStmtLst(ast::StmtLstNode *stmtlst_node) {
  for (auto &stmt_node : stmtlst_node->get_children()) {
    stmt_node->AcceptVisitor(this);
  }
}

void ProgramValidator::VisitCall(ast::CallNode *call_node) {
  auto proc_name = call_node->get_var()->get_name();
  call_names_.push_back(proc_name);
}

}  // namespace sp
