#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/ContainerNode.h"

namespace ast {
class WhileNode : public ContainerNode {
 public:
  WhileNode(std::unique_ptr<CondExprNode> cond,
            std::unique_ptr<StmtLstNode> stmts, int line)
      : ContainerNode(line) {
    cond_ = std::move(cond);
    stmts_.push_back(std::move(stmts));
  }

  void AcceptVisitor(sp::TNodeVisitor*) override;

  inline std::unique_ptr<CondExprNode>& get_cond() { return cond_; }
  inline std::unique_ptr<StmtLstNode>& get_stmts() { return stmts_.front(); }

 private:
  std::unique_ptr<CondExprNode> cond_;
};
}  // namespace ast
