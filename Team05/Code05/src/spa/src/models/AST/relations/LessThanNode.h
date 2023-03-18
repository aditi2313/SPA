#pragma once

#include <memory>
#include <utility>

#include "RelExprNode.h"
#include "common/Utiity.h"

namespace ast {
class LessThanNode : public RelExprNode {
 public:
  LessThanNode(std::unique_ptr<RelFactor> left_factor,
               std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  bool DeepEquals(const CondExprNode& other) override {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<LessThanNode, CondExprNode>(other);
  }
};
}  // namespace ast
