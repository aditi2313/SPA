#pragma once
#include <memory>
#include <utility>
#include <string>

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
  inline std::unique_ptr<ExprNode> get_expr_copy() { return expr_->Copy(); }

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
  inline std::string get_var_name() { return var_->get_name(); }

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
  inline std::string get_var_name() { return var_->get_name(); }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
};

class CallNode : public StmtNode {
 public:
  explicit CallNode(std::unique_ptr<VarNode> var, int line) : StmtNode(line) {
    var_ = std::move(var);
  }

  inline std::unique_ptr<VarNode>& get_var() { return var_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<VarNode> var_;
};

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
