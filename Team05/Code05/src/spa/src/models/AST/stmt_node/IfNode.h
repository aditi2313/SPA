#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class IfNode : public StmtNode {
 public:
  IfNode(std::unique_ptr<CondExprNode> cond, std::unique_ptr<StmtLstNode> pos,
         std::unique_ptr<StmtLstNode> neg, int line)
      : StmtNode(line) {
    cond_ = std::move(cond);
    then_ = std::move(pos);
    else_ = std::move(neg);
  }

  void AcceptVisitor(sp::TNodeVisitor* visitor);

  inline std::unique_ptr<CondExprNode>& get_cond() { return cond_; }
  inline std::unique_ptr<StmtLstNode>& get_then() { return then_; }
  inline std::unique_ptr<StmtLstNode>& get_else() { return else_; }

 private:
  std::unique_ptr<CondExprNode> cond_;
  std::unique_ptr<StmtLstNode> then_;
  std::unique_ptr<StmtLstNode> else_;
};
}  // namespace ast
