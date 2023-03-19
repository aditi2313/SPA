#pragma once

#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/DoubleCondExprNode.h"

namespace ast {
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
}  // namespace ast
