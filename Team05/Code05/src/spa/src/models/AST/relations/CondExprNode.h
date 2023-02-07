#pragma once

#include <memory>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"

namespace ast {
class CondExprNode : public TNode {};





/// <summary>
/// A conditional expression with two
/// sub conditions.
/// </summary>
class DoubleCondExprNode : public CondExprNode {
 public:
  DoubleCondExprNode(auto left_cond, auto right_cond) {
    left_cond_ = std::move(left_cond);
    right_cond_ = std::move(right_cond);
  }

 protected:
  std::unique_ptr<CondExprNode> left_cond_;
  std::unique_ptr<CondExprNode> right_cond_;
};

class AndExprNode : public DoubleCondExprNode {
 public:
};

class OrExprNode : public DoubleCondExprNode {
 public:
};

class NotExprNode : public CondExprNode {
 public:
  NotExprNode(auto cond) { cond_ = std::move(cond); }

 private:
  std::unique_ptr<CondExprNode> cond_;
};

}  // namespace ast