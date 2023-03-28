#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "PKB/PKBWrite.h"
#include "ProcedureProcessingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"
#include "common/filter/filters/Export.h"
#include "common/logging/Logger.h"

namespace sp {
class ModifiesVisitor : public ProcedureProcessingVisitor {
 public:
  explicit ModifiesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : ProcedureProcessingVisitor(
            std::move(pkb_ptr),
            [&](pkb::Key key, std::unordered_set<std::string> variables) {
              pkb_ptr_->AddModifiesData(key, variables);
            }) {}

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::ReadNode* read_node) override;

  void ProcessAft(ast::IfNode*) override;
  void ProcessAft(ast::WhileNode*) override;

 private:
  inline void AddVariablesFromStmtList(
      ast::StmtLstNode& node, std::unordered_set<std::string>& vars) override {
    auto pkb = pkb_ptr_->EndWrite();
    pkb::PKBRead reader(std::move(pkb));
    for (auto& child : node.get_children()) {
      filter::ModifiesIndexFilter filter(child->get_line());
      auto& result = reader.Modifies(filter);
      while (!result.reached_end()) {
        auto& modifies_data = result.read_data();
        auto variables = modifies_data.get_variables();
        vars.merge(variables);
      }
    }
    pkb = reader.EndRead();
    pkb_ptr_ = std::make_unique<pkb::PKBWrite>(std::move(pkb));
  }
};
}  // namespace sp
