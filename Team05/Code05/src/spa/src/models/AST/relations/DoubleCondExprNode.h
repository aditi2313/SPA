#pragma once

#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"

namespace ast {
/// <summary>
/// A conditional expression with two
/// sub conditions.
/// </summary>
class DoubleCondExprNode : public CondExprNode {
 public:
  DoubleCondExprNode(std::unique_ptr<CondExprNode> left_cond,
                     std::unique_ptr<CondExprNode> right_cond) {
    left_cond_ = std::move(left_cond);
    right_cond_ = std::move(right_cond);
  }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  bool DeepEquals(const CondExprNode& other) override {
    if (dynamic_cast<const DoubleCondExprNode*>(&other)) {
      const DoubleCondExprNode& o_a =
          dynamic_cast<const DoubleCondExprNode&>(other);
      return o_a.left_cond_->DeepEquals(*left_cond_) &&
             o_a.right_cond_->DeepEquals(*right_cond_);
    }
    return false;
  }

  std::unique_ptr<CondExprNode>& get_left_cond() { return left_cond_; }

  std::unique_ptr<CondExprNode>& get_right_cond() { return right_cond_; }

 protected:
  std::unique_ptr<CondExprNode> left_cond_;
  std::unique_ptr<CondExprNode> right_cond_;
};
}  // namespace ast
