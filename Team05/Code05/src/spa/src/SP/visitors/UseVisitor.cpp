#include "SP/visitors/ExpressionVisitor.h"
#include "UseVisitor.h"

namespace sp {
void UseVisitor::VisitProgram(ast::ProgramNode* program_node) {
  for (auto& child : program_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void UseVisitor::VisitProc(ast::ProcNode* proc_node) {
  proc_node->get_children()->AcceptVisitor(this);
}

void UseVisitor::VisitStmtLst(ast::StmtLstNode* stmtlst_node) {
  for (auto& child : stmtlst_node->get_children()) {
    child->AcceptVisitor(this);
  }
}

void UseVisitor::VisitAssign(ast::AssignNode* assign_node) {
  ExpressionVisitor exprVisitor;
  assign_node->get_expr()->AcceptVisitor(&exprVisitor);
  std::set<std::string> vars = exprVisitor.get_vars();
  // pkb_ptr_->AddUseData(read_node->get_line(), vars);
}


void UseVisitor::VisitPrint(ast::PrintNode* print_node) {
  //std::vector<std::string> vars = {read_node->get_var()->get_name()};
  //pkb_ptr_->AddUseData(read_node->get_line(), vars);
}


}  // namespace sp