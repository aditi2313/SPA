#pragma once

#include "CondExprNode.h"

namespace ast {
/// <summary>
/// A Relation factor. Shouldn't be used
/// for structural comparisons. Simplty a wrapper.
/// Contains an expression.
/// </summary>
class RelFactor : public TNode {
 public:
  RelFactor(std::unique_ptr<ExprNode> expression) {
    expression_ = std::move(expression);
  }
  const std::unique_ptr<ExprNode>& get_ref() { return expression_; }

 protected:
  std::unique_ptr<ExprNode> expression_;
};

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

 protected:
  std::unique_ptr<RelFactor> left_factor_;
  std::unique_ptr<RelFactor> right_factor_;
};

class MoreThanNode : public RelExprNode {};
class LessThanNode : public RelExprNode {};
class MoreThanEqualNode : public RelExprNode {};
class LessThanEqualNode : public RelExprNode {};
class EqualNode : public RelExprNode {};

}  // namespace ast