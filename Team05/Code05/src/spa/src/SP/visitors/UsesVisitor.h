#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class UsesVisitor : public PKBWritingVisitor {
 public:
  explicit UsesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::PrintNode* print_node) override;

  void Process(ast::IfNode* if_node) override;

  void Process(ast::WhileNode* while_node) override;

 private:
  void AddVariablesFromStmtList(ast::StmtLstNode& node,
                                std::unordered_set<std::string>& vars);
};
}  // namespace sp
