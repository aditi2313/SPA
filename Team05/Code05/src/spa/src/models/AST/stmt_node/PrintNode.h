#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/stmt_node/SingleVarStmtNode.h"

namespace ast {
class PrintNode : public SingleVarStmtNode {
 public:
  explicit PrintNode(std::unique_ptr<VarNode> var, int line)
      : SingleVarStmtNode(std::move(var), line) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;
};
}  // namespace ast
