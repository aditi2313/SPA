#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class ModifiesVisitor : public PKBWritingVisitor {
 public:
  explicit ModifiesVisitor(std::unique_ptr<pkb::PKBWrite>&& pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void Process(ast::AssignNode* assign_node) override;

  void Process(ast::ReadNode* read_node) override;

  // TODO(Gab) Go into call node and get the information #41
  void Process(ast::CallNode* call_node) override {}
};
}  // namespace sp
