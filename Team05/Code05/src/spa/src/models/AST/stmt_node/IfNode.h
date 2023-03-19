#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/ContainerNode.h"

namespace ast {
class IfNode : public ContainerNode {
 public:
  IfNode(std::unique_ptr<CondExprNode> cond, std::unique_ptr<StmtLstNode> pos,
         std::unique_ptr<StmtLstNode> neg, int line)
      : ContainerNode(line) {
    cond_ = std::move(cond);
    stmts_.push_back(std::move(pos));
    stmts_.push_back(std::move(neg));
  }

  void AcceptVisitor(sp::TNodeVisitor* visitor);

  inline std::unique_ptr<CondExprNode>& get_cond() { return cond_; }
  inline std::unique_ptr<StmtLstNode>& get_then() { return stmts_.at(kThen); }
  inline std::unique_ptr<StmtLstNode>& get_else() { return stmts_.at(kElse); }

 private:
  std::unique_ptr<CondExprNode> cond_;
  inline static const int kThen = 0;
  inline static const int kElse = 1;
};
}  // namespace ast
