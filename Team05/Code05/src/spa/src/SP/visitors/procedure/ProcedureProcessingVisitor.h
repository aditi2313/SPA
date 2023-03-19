#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "PKB/tables/IndexableTable.h"
#include "SP/visitors/PKBWritingVisitor.h"

namespace sp {
class ProcedureProcessingVisitor : public PKBWritingVisitor {
 public:
  explicit ProcedureProcessingVisitor(
      std::unique_ptr<pkb::PKBWrite>&& pkb_ptr,
      std::function<void(pkb::IntOrStringVariant,
                         std::unordered_set<std::string>)>
          adding_function)
      : PKBWritingVisitor(std::move(pkb_ptr)),
        adding_function_(adding_function) {}

  void ProcessAft(ast::ProgramNode* program_node) override;

  void Process(ast::ProcNode* proc_node) override;

  void Process(ast::IfNode* if_node) override;

  void Process(ast::WhileNode* while_node) override;

  void Process(ast::CallNode* call_node) override;

 protected:
  virtual void AddVariablesFromStmtList(
      ast::StmtLstNode& node, std::unordered_set<std::string>& vars) = 0;

  // The mapping from procedure to directly used data
  std::unordered_map<std::string, std::unordered_set<std::string>> direct_data_;
  std::string current_procedure_;

 private:
  // Mapping from a procedure to the procedures which call it
  std::unordered_map<std::string, std::unordered_set<std::string>> called_by_;
  // Mapping from a procedure to the calls within the procedure
  std::unordered_map<std::string, std::unordered_set<std::string>> proc_calls_;

  // Mapping from call to procedure that it is in
  std::unordered_map<int, std::string> call_to_proc_;

  // mapping from procedure to lines that call said procedure
  std::unordered_map<std::string, std::unordered_set<int>> proc_called_by_line_;
  std::vector<ast::ContainerNode*> containers_visited_;

  std::function<void(pkb::IntOrStringVariant, std::unordered_set<std::string>)>
      adding_function_;
};

}  // namespace sp
