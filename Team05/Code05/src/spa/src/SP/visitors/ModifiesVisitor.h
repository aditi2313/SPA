#pragma once

#include <string>
#include <vector>

#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class ModifiesVisitor : public TNodeVisitor {
 public:
  ModifiesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : TNodeVisitor(std::move(pkb_ptr)) {}

  void VisitProgram(ast::ProgramNode* program_node);

  void VisitProc(ast::ProcNode* proc_node);

  void VisitStmtLst(ast::StmtLstNode* stmtlst_node);

  void VisitAssign(ast::AssignNode* assign_node);

  void VisitRead(ast::ReadNode* read_node);

  void VisitPrint(ast::PrintNode* print_node) {}

  void VisitFactor(ast::FactorNode* factor_node) {}

  void VisitExpr(ast::ExprNode* expr_node) {}

  void VisitTerm(ast::TermNode* term_node) {}

  void VisitVar(ast::VarNode* var_node) {}

  void VisitConst(ast::ConstNode* const_node) {}

  void VisitPlus(ast::PlusNode* plus_node) {}

  void VisitMinus(ast::MinusNode* minus_node) {}

  void VisitTimes(ast::TimesNode* times_node) {}

  void VisitDiv(ast::DivNode* div_node) {}

  void VisitMod(ast::ModNode* mod_node) {}
};
}  // namespace sp