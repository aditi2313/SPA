#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class DataVisitor : public PKBWritingVisitor {
 public:
  explicit DataVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void Process(ast::ProcNode* proc_node) override;

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::ReadNode* read_node) override;

  void Process(ast::PrintNode* print_node) override;

  void Process(ast::VarNode* var_node) override;

  void Process(ast::ConstNode* const_node) override;

  void Process(ast::CallNode* call_node) override;

  void Process(ast::WhileNode* while_node) override;

  void Process(ast::IfNode* if_node) override;
};
}  // namespace sp
