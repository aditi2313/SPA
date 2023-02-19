#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class FollowsVisitor : public PKBWritingVisitor {
 public:
  explicit FollowsVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void VisitProgram(ast::ProgramNode* program_node) override;

  void VisitProc(ast::ProcNode* proc_node) override;

  void VisitStmtLst(ast::StmtLstNode* stmtlst_node) override;

  void VisitIf(ast::IfNode* if_node) override;

  void VisitWhile(ast::WhileNode* while_node) override;
};
}  // namespace sp