#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "PKB/PKBWrite.h"
#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/logging/Logger.h"

namespace sp {
class ModifiesVisitor : public PKBWritingVisitor {
 public:
  explicit ModifiesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void ProcessAft(ast::ProgramNode* program_node) override;

  void Process(ast::ProcNode* proc_node) override;

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::ReadNode* read_node) override;

  void Process(ast::CallNode* call_node) override;

  void ProcessAft(ast::IfNode*) override;
  void ProcessAft(ast::WhileNode*) override;

 private:
  void AddVariablesFromStmtList(ast::StmtLstNode& node,
                                std::unordered_set<std::string>& vars) {
    auto pkb = pkb_ptr_->EndWrite();
    pkb::PKBRead reader(std::move(pkb));
    for (auto& child : node.get_children()) {
      auto result = reader
                        .Modifies(std::make_unique<filter::ModifiesIndexFilter>(
                            child->get_line()))
                        ->get_result();
      if (result->empty()) continue;
      auto variables = result->get_row(child->get_line()).get_variables();
      vars.merge(variables);
    }
    pkb = reader.EndRead();
    pkb_ptr_ = std::make_unique<pkb::PKBWrite>(std::move(pkb));
  }

  // Mapping from a procedure to the variables it modifies directly
  std::unordered_map<std::string, std::unordered_set<std::string>>
      direct_modifies_;
  // Mapping from a procedure to the procedures which call it
  std::unordered_map<std::string, std::unordered_set<std::string>> called_by_;
  // Mapping from a procedure to the calls within the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>> proc_calls_;
  std::string current_procedure_;
};
}  // namespace sp
