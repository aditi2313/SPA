#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"

namespace ast {
class StmtLstNode;
class StmtNode : public TNode {
 public:
  explicit StmtNode(int line) : line_(line) {}

  virtual int get_line() { return line_; }

  virtual void AcceptVisitor(sp::TNodeVisitor* visitor) = 0;

 private:
  int line_;
};
}  // namespace ast
