#pragma once

#include <memory>
#include <utility>

#include "RelExprNode.h"
#include "common/Utility.h"

namespace ast {
class EqualNode : public RelExprNode {
 public:
  EqualNode(std::unique_ptr<RelFactor> left_factor,
            std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  bool DeepEquals(const CondExprNode& other) override {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<EqualNode, CondExprNode>(other);
  }
};
}  // namespace ast
