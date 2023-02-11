#pragma once

#include <memory>
#include <utility>

#include "CondExprNode.h"
#include "common/Utiity.h"

namespace ast {
/// <summary>
/// A Relation factor. Shouldn't be used
/// for structural comparisons. Simplty a wrapper.
/// Contains an expression.
/// </summary>
class RelFactor : public TNode {
 public:
  explicit RelFactor(std::unique_ptr<ExprNode> expression) {
    expression_ = std::move(expression);
  }
  const std::unique_ptr<ExprNode>& get_ref() { return expression_; }

  virtual void AcceptVisitor(sp::TNodeVisitor* visitor);

  friend bool operator==(const RelFactor& LHS, const RelFactor& RHS) {
    return LHS.expression_->DeepEquals(*(RHS.expression_));
  }

  std::unique_ptr<ExprNode>& get_expr() { return expression_; }

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

  virtual void AcceptVisitor(sp::TNodeVisitor* visitor);

  virtual bool DeepEquals(const CondExprNode& other) {
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

class MoreThanNode : public RelExprNode {
 public:
  MoreThanNode(std::unique_ptr<RelFactor> left_factor,
               std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  virtual bool DeepEquals(const CondExprNode& other) {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<MoreThanNode, CondExprNode>(other);
  }
};
class LessThanNode : public RelExprNode {
 public:
  LessThanNode(std::unique_ptr<RelFactor> left_factor,
               std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  virtual bool DeepEquals(const CondExprNode& other) {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<LessThanNode, CondExprNode>(other);
  }
};
class MoreThanEqualNode : public RelExprNode {
 public:
  MoreThanEqualNode(std::unique_ptr<RelFactor> left_factor,
                    std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}

  virtual bool DeepEquals(const CondExprNode& other) {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<MoreThanEqualNode, CondExprNode>(other);
  }
};
class LessThanEqualNode : public RelExprNode {
 public:
  LessThanEqualNode(std::unique_ptr<RelFactor> left_factor,
                    std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  virtual bool DeepEquals(const CondExprNode& other) {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<LessThanEqualNode, CondExprNode>(other);
  }
};
class EqualNode : public RelExprNode {
 public:
  EqualNode(std::unique_ptr<RelFactor> left_factor,
            std::unique_ptr<RelFactor> right_factor)
      : RelExprNode(std::move(left_factor), std::move(right_factor)) {}
  virtual bool DeepEquals(const CondExprNode& other) {
    return RelExprNode::DeepEquals(other) &&
           util::InstanceOf<EqualNode, CondExprNode>(other);
  }
};

}  // namespace ast
