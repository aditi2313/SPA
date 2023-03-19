#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class AssignNode : public StmtNode {
 public:
  explicit AssignNode(std::unique_ptr<VarNode> var,
                      std::unique_ptr<ExprNode> expr, int line)
      : StmtNode(line) {
    var_ = std::move(var);
    expr_ = std::move(expr);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }
  inline std::string get_var_name() { return var_->get_name(); }

  inline std::unique_ptr<ExprNode>& get_expr() { return expr_; }
  inline std::unique_ptr<ExprNode> move_expr() { return std::move(expr_); }
  inline std::unique_ptr<ExprNode> get_expr_copy() { return expr_->Copy(); }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
  std::unique_ptr<ExprNode> expr_;
};
}  // namespace ast
