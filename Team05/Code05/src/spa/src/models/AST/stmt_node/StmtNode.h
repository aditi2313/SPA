#pragma once
#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"

namespace ast {
class StatementNode : public TNode {};

class AssignNode : public StatementNode {
 public:
  explicit AssignNode(std::unique_ptr<VarNode> var,
                      std::unique_ptr<ExprNode> exp) {
    var_ = std::move(var);
    exp_ = std::move(exp);
  }

 private:
  std::unique_ptr<VarNode> var_;
  std::unique_ptr<ExprNode> exp_;
};

class ReadNode : public StatementNode {
 public:
  explicit ReadNode(std::unique_ptr<VarNode> var) { var_ = std::move(var); }

 private:
  std::unique_ptr<VarNode> var_;
};

class PrintNode : public StatementNode {
 public:
  explicit PrintNode(std::unique_ptr<VarNode> var) { var_ = std::move(var); }

 private:
  std::unique_ptr<VarNode> var_;
};
}  // namespace ast
