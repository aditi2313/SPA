#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class UsesVisitor : public PKBWritingVisitor {
 public:
  explicit UsesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void VisitProgram(ast::ProgramNode* program_node) override;

  void VisitProc(ast::ProcNode* proc_node) override;

  void VisitStmtLst(ast::StmtLstNode* stmtlst_node) override;

  void VisitAssign(ast::AssignNode* assign_node) override;

  void VisitPrint(ast::PrintNode* assign_node) override;

  void VisitIf(ast::IfNode* if_node) override;

  void VisitWhile(ast::WhileNode* while_node) override;

 private:
  void AddVariablesFromStmtList(pkb::PKBRead& pkb_read, ast::StmtLstNode& node,
                                std::unordered_set<std::string>&);
};
}  // namespace sp
