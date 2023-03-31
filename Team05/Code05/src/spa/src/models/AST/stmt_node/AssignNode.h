#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/SingleVarStmtNode.h"

namespace ast {
class AssignNode : public SingleVarStmtNode {
 public:
  explicit AssignNode(std::unique_ptr<VarNode> var,
                      std::unique_ptr<ExprNode> expr, int line)
      : SingleVarStmtNode(std::move(var), line) {
    expr_ = std::move(expr);
  }

  inline std::unique_ptr<ExprNode>& get_expr() { return expr_; }
  inline std::unique_ptr<ExprNode> move_expr() { return std::move(expr_); }
  inline std::unique_ptr<ExprNode> get_expr_copy() { return expr_->Copy(); }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<ExprNode> expr_;
};
}  // namespace ast
