#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class UsesVisitor : public PKBWritingVisitor {
 public:
  explicit UsesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void PerformWork(ast::AssignNode* assign_node) override;

  void PerformWork(ast::PrintNode* assign_node) override;

  void PerformWork(ast::IfNode* if_node) override;

  void PerformWork(ast::WhileNode* while_node) override;
};
}  // namespace sp
