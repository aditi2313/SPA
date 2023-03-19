#pragma once

#include <memory>
#include <utility>

#include "RelFactor.h"
#include "common/Utility.h"

namespace ast {
/// <summary>
/// A relation expression node. Used for binary relation comparisons
/// between two relation factors.
/// </summary>
class RelExprNode : public CondExprNode {
 public:
  RelExprNode(std::unique_ptr<RelFactor> left_factor,
              std::unique_ptr<RelFactor> right_factor) {
    left_factor_ = std::move(left_factor);
    right_factor_ = std::move(right_factor);
  }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  bool DeepEquals(const CondExprNode& other) override {
    if (util::InstanceOf<RelExprNode, CondExprNode>(other)) {
      const auto& other_rel = dynamic_cast<const RelExprNode&>(other);
      return *(other_rel.left_factor_) == *(left_factor_) &&
             *(other_rel.right_factor_) == *(right_factor_);
    }
    return false;
  }

  std::unique_ptr<RelFactor>& get_left_factor() { return left_factor_; }

  std::unique_ptr<RelFactor>& get_right_factor() { return right_factor_; }

 protected:
  std::unique_ptr<RelFactor> left_factor_;
  std::unique_ptr<RelFactor> right_factor_;
};
}  // namespace ast
