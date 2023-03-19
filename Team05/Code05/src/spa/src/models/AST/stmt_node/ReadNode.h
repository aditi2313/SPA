#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class ReadNode : public StmtNode {
 public:
  explicit ReadNode(std::unique_ptr<VarNode> var, int line) : StmtNode(line) {
    var_ = std::move(var);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }
  inline std::string get_var_name() { return var_->get_name(); }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
};
}  // namespace ast
