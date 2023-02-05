#pragma once
#include <memory>
#include <utility>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"

namespace ast {
class StmtNode : public TNode {
 public:
  explicit StmtNode(int line) : line_(line) {}

  virtual int get_line() { return line_; }

 private:
  int line_;
};

class AssignNode : public StmtNode {
 public:
  explicit AssignNode(std::unique_ptr<VarNode> var,
                      std::unique_ptr<ExprNode> expr, int line)
      : StmtNode(line) {
    var_ = std::move(var);
    expr_ = std::move(expr);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }

  inline std::unique_ptr<ExprNode>& get_expr() { return expr_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
  std::unique_ptr<ExprNode> expr_;
};

class ReadNode : public StmtNode {
 public:
  explicit ReadNode(std::unique_ptr<VarNode> var, int line) : StmtNode(line) {
    var_ = std::move(var);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
};

class PrintNode : public StmtNode {
 public:
  explicit PrintNode(std::unique_ptr<VarNode> var, int line) : StmtNode(line) {
    var_ = std::move(var);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  // TODO(nhjryan): implement nodes for if-else and while loops

 private:
  std::unique_ptr<VarNode> var_;
};

class CallNode : public StmtNode {
 public:
  explicit CallNode(std::unique_ptr<VarNode> var, int line) : StmtNode(line) {
    var_ = std::move(var);
  }

 private:
    std::unique_ptr<VarNode> var_;
};
}  // namespace ast
