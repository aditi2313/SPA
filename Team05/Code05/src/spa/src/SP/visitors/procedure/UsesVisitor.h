#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "ProcedureProcessingVisitor.h"

namespace sp {
class UsesVisitor : public ProcedureProcessingVisitor {
 public:
  explicit UsesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : ProcedureProcessingVisitor(
            std::move(pkb_ptr), [&](pkb::IntOrStringVariant key,
                                    std::unordered_set<std::string> variables) {
              pkb_ptr_->AddUsesData(key, variables);
            }) {}

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::PrintNode* print_node) override;

  void ProcessAft(ast::IfNode* if_node) override;

  void ProcessAft(ast::WhileNode* while_node) override;

 private:
  void AddVariablesFromStmtList(ast::StmtLstNode& node,
                                std::unordered_set<std::string>& vars) override;
};
}  // namespace sp
