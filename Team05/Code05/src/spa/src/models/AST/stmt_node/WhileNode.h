#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class WhileNode : public StmtNode {
 public:
  WhileNode(std::unique_ptr<CondExprNode> cond,
            std::unique_ptr<StmtLstNode> stmts, int line)
      : StmtNode(line) {
    cond_ = std::move(cond);
    stmts_ = std::move(stmts);
  }

  void AcceptVisitor(sp::TNodeVisitor*) override;

  inline std::unique_ptr<CondExprNode>& get_cond() { return cond_; }
  inline std::unique_ptr<StmtLstNode>& get_stmts() { return stmts_; }

 private:
  std::unique_ptr<CondExprNode> cond_;
  std::unique_ptr<StmtLstNode> stmts_;
};
}  // namespace ast
