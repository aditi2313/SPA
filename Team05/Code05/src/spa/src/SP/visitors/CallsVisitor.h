#pragma once

#include "PKBWritingVisitor.h"
#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class CallsVisitor : public PKBWritingVisitor {
 public:
  explicit CallsVisitor(std::unique_ptr<pkb::PKBWrite> &&pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void Process(ast::CallNode* call_node) override;
};
}  // namespace sp
