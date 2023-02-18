#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "CallValidator.h"
#include "ProcedureValidator.h"
#include "SP/visitors/ValidatorVisitor.h"
#include "Validator.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class ProgramValidator : public Validator, ValidatorVisitor {
 public:
  explicit ProgramValidator(std::unique_ptr<ast::ProgramNode>& root)
      : root_(root) {}

  bool Validate() override;

  void VisitProgram(ast::ProgramNode* program_node) override;
  void VisitProc(ast::ProcNode* proc_node) override;
  void VisitStmtLst(ast::StmtLstNode* stmtlst_node) override;
  void VisitAssign(ast::AssignNode* assign_node) override{};
  void VisitRead(ast::ReadNode* read_node) override{};
  void VisitPrint(ast::PrintNode* print_node) override{};
  void VisitCall(ast::CallNode* call_node) override;

  void VisitExpr(ast::ExprNode* expr_node) override{};

  void VisitVar(ast::VarNode* var_node) override{};
  void VisitConst(ast::ConstNode* const_node) override{};

 private:
  std::unique_ptr<ast::ProgramNode>& root_;
  sp::ProcedureValidator procedure_validator_;
  sp::CallValidator call_validator_;
};
}  // namespace sp
