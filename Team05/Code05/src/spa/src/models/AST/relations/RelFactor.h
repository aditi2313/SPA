#pragma once

#include <memory>
#include <utility>

#include "CondExprNode.h"
#include "common/Utility.h"

namespace ast {
/// <summary>
/// A Relation factor. Shouldn't be used
/// for structural comparisons. Simply a wrapper.
/// Contains an expression.
/// </summary>
class RelFactor : public TNode {
 public:
  explicit RelFactor(std::unique_ptr<ExprNode> expression) {
    expression_ = std::move(expression);
  }
  const std::unique_ptr<ExprNode>& get_ref() { return expression_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  friend bool operator==(const RelFactor& LHS, const RelFactor& RHS) {
    return LHS.expression_->DeepEquals(*(RHS.expression_));
  }

  std::unique_ptr<ExprNode>& get_expr() { return expression_; }

 protected:
  std::unique_ptr<ExprNode> expression_;
};
}  // namespace ast
