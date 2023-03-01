#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
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

  void ProcessAfter(ast::ProgramNode* program_node) override;

  void Process(ast::ProcNode* proc_node) override;

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::PrintNode* print_node) override;

  void Process(ast::IfNode* if_node) override;

  void Process(ast::WhileNode* while_node) override;

  void Process(ast::CallNode* call_node) override;

 private:
  void AddVariablesFromStmtList(ast::StmtLstNode& node,
                                std::unordered_set<std::string>& vars);

  // Mapping from procedure name to the variables used directly
  std::unordered_map<std::string, std::unordered_set<std::string>>
      proc_direct_uses_;

  // Mapping from procedure name to calls within the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>> proc_calls_;
};
}  // namespace sp
