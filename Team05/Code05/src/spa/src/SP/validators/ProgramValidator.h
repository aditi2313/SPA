#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "SP/visitors/ValidatorVisitor.h"
#include "Validator.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class ProgramValidator : public Validator, ValidatorVisitor {
 public:
  explicit ProgramValidator(std::unique_ptr<ast::ProgramNode> &root)
      : root_(root) {}

  bool Validate() override;

  void VisitProgram(ast::ProgramNode *program_node) override;
  void VisitProc(ast::ProcNode* proc_node) override;
  void VisitStmtLst(ast::StmtLstNode* stmtlst_node) override;
  void VisitAssign(ast::AssignNode* assign_node) override;
  void VisitRead(ast::ReadNode* read_node) override;
  void VisitPrint(ast::PrintNode* print_node) override;
  void VisitCall(ast::CallNode* call_node) override;

  void VisitFactor(ast::FactorNode* factor_node) override {};
  void VisitExpr(ast::ExprNode* expr_node) override {};
  void VisitTerm(ast::TermNode* term_node) override {};
  void VisitVar(ast::VarNode* var_node) override {};
  void VisitConst(ast::ConstNode* const_node) override {};
  void VisitPlus(ast::PlusNode* plus_node) override {};
  void VisitMinus(ast::MinusNode* minus_node) override {};
  void VisitTimes(ast::TimesNode* times_node) override {};
  void VisitDiv(ast::DivNode* div_node) override {};
  void VisitMod(ast::ModNode* mod_node) override {};

 private:
  std::unique_ptr<ast::ProgramNode> &root_;
  std::vector<std::string> procedure_names_;
  std::vector<std::string> call_names_;
};
}  // namespace sp
