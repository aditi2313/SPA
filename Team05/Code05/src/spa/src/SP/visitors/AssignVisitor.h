#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class AssignVisitor : public PKBWritingVisitor {
 public:
  explicit AssignVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void VisitStmtLst(ast::StmtLstNode* stmtlst_node) override;

  void VisitAssign(ast::AssignNode* assign_node) override;
};
}  // namespace sp
