#pragma once

#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"

namespace ast {
class CondExprNode : public TNode {
 public:
  virtual bool DeepEquals(const CondExprNode& other) = 0;
  void AcceptVisitor(sp::TNodeVisitor* visitor) override {}
};

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

class AndExprNode : public DoubleCondExprNode {
 public:
  AndExprNode(std::unique_ptr<CondExprNode> left_cond,
              std::unique_ptr<CondExprNode> right_cond)
      : DoubleCondExprNode(std::move(left_cond), std::move(right_cond)) {}
  bool DeepEquals(const CondExprNode& other) override {
    return DoubleCondExprNode::DeepEquals(other) &&
           dynamic_cast<const AndExprNode*>(&other);
  }
};

class OrExprNode : public DoubleCondExprNode {
 public:
  OrExprNode(std::unique_ptr<CondExprNode> left_cond,
             std::unique_ptr<CondExprNode> right_cond)
      : DoubleCondExprNode(std::move(left_cond), std::move(right_cond)) {}
  bool DeepEquals(const CondExprNode& other) override {
    return DoubleCondExprNode::DeepEquals(other) &&
           dynamic_cast<const OrExprNode*>(&other);
  }
};

class NotExprNode : public CondExprNode {
 public:
  explicit NotExprNode(std::unique_ptr<CondExprNode> cond) {
    cond_ = std::move(cond);
  }

  bool DeepEquals(const CondExprNode& other) override {
    if (dynamic_cast<const NotExprNode*>(&other)) {
      const NotExprNode& o_a = dynamic_cast<const NotExprNode&>(other);
      return o_a.cond_->DeepEquals(*cond_);
    }
    return false;
  }

  std::unique_ptr<CondExprNode> get_cond() { return cond_; }

 private:
  std::unique_ptr<CondExprNode> cond_;
};

}  // namespace ast
