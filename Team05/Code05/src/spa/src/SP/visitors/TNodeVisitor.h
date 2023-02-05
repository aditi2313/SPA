#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKB/PKBWrite.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class TNodeVisitor {
 public:
  explicit TNodeVisitor(std::unique_ptr<pkb::PKBWrite> pkb_ptr) {}

  virtual void VisitProgram(ast::ProgramNode* program_node) = 0;

  virtual void VisitProc(ast::ProcNode* proc_node) = 0;

  virtual void VisitAssign(ast::ProcNode* proc_node) = 0;

  virtual void VisitRead(ast::ReadNode* read_node) = 0;

  virtual void VisitPrint(ast::PrintNode* print_node) = 0;

  virtual void VisitFactor(ast::FactorNode* factor_node) = 0;

  virtual void VisitExpr(ast::ExprNode* expr_node) = 0;

  virtual void VisitTerm(ast::TermNode* term_node) = 0;

  virtual void VisitVar(ast::VarNode* var_node) = 0;

  virtual void VisitConst(ast::ConstNode* const_node) = 0;

  virtual void VisitPlus(ast::PlusNode* plus_node) = 0;

  virtual void VisitMinus(ast::MinusNode* minus_node) = 0;

  virtual void VisitTimes(ast::TimesNode* times_node) = 0;

  virtual void VisitDiv(ast::DivNode* div_node) = 0;

  virtual void VisitMod(ast::ModNode* mod_node) = 0;

 private:
  std::unique_ptr<pkb::PKBWrite> pkb_ptr;
};
}  // namespace sp