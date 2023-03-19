#pragma once

#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"

namespace ast {
class NotExprNode : public CondExprNode {
 public:
  explicit NotExprNode(std::unique_ptr<CondExprNode> cond) {
    cond_ = std::move(cond);
  }

  void AcceptVisitor(sp::TNodeVisitor*) override;

  bool DeepEquals(const CondExprNode& other) override {
    if (dynamic_cast<const NotExprNode*>(&other)) {
      const NotExprNode& o_a = dynamic_cast<const NotExprNode&>(other);
      return o_a.cond_->DeepEquals(*cond_);
    }
    return false;
  }

  std::unique_ptr<CondExprNode>& get_cond() { return cond_; }

 private:
  std::unique_ptr<CondExprNode> cond_;
};
}  // namespace ast
