#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SP/visitors/TNodeVisitor.h"
#include "PKBWritingVisitor.h"

namespace sp {

class ParentVisitor  : public PKBWritingVisitor {
 public:
  explicit ParentVisitor(std::unique_ptr<pkb::PKBWrite> &&pkb_ptr)
      : PKBWritingVisitor(std::move(pkb_ptr)) {}

  void Process(ast::IfNode* if_node) override;

  void Process(ast::WhileNode* while_node) override;
};
}  // namespace sp
