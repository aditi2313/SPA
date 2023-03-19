#pragma once

#include <memory>
#include <utility>

#include "RelExprNode.h"
#include "common/Utility.h"

namespace ast {
class MoreThanEqualNode : public RelExprNode {
 public:
  MoreThanEqualNode(std::unique_ptr<RelFactor> left_factor,
                    std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}

  bool DeepEquals(const CondExprNode& other) override {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<MoreThanEqualNode, CondExprNode>(other);
  }
};
}  // namespace ast
