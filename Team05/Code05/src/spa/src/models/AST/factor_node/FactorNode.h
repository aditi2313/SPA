#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/TNode.h"

namespace ast {
class FactorNode : public TNode {};

class ExprNode : public FactorNode {};

class TermNode : public ExprNode {};

class VarNode : public FactorNode {
 public:
  explicit VarNode(std::string var_name) : var_name_(var_name) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  inline std::string get_name() { return var_name_; }

 private:
  std::string var_name_;
};

class ConstNode : public FactorNode {
 public:
  explicit ConstNode(int val) : val_(val) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  inline int get_val() { return val_; }

 private:
  int val_;
};

class PlusNode : public ExprNode {
 public:
  explicit PlusNode(std::unique_ptr<ExprNode> expr,
                    std::unique_ptr<TermNode> term) {
    expr_ = std::move(expr);
    term_ = std::move(term);
  }

  inline std::unique_ptr<ExprNode>& get_expr() { return expr_; }

  inline std::unique_ptr<TermNode>& get_term() { return term_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<ExprNode> expr_;
  std::unique_ptr<TermNode> term_;
};

class MinusNode : public ExprNode {
 public:
  explicit MinusNode(std::unique_ptr<ExprNode> expr,
                     std::unique_ptr<TermNode> term) {
    expr_ = std::move(expr);
    term_ = std::move(term);
  }

  inline std::unique_ptr<ExprNode>& get_expr() { return expr_; }

  inline std::unique_ptr<TermNode>& get_term() { return term_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<ExprNode> expr_;
  std::unique_ptr<TermNode> term_;
};

class TimesNode : public TermNode {
 public:
  explicit TimesNode(std::unique_ptr<TermNode> term,
                     std::unique_ptr<FactorNode> factor) {
    term_ = std::move(term);
    factor_ = std::move(factor);
  }

  inline std::unique_ptr<TermNode>& get_term() { return term_; }

  inline std::unique_ptr<FactorNode>& get_factor() { return factor_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<TermNode> term_;
  std::unique_ptr<FactorNode> factor_;
};

class DivNode : public TermNode {
 public:
  explicit DivNode(std::unique_ptr<TermNode> term,
                   std::unique_ptr<FactorNode> factor) {
    term_ = std::move(term);
    factor_ = std::move(factor);
  }

  inline std::unique_ptr<TermNode>& get_term() { return term_; }

  inline std::unique_ptr<FactorNode>& get_factor() { return factor_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<TermNode> term_;
  std::unique_ptr<FactorNode> factor_;
};

class ModNode : public TermNode {
 public:
  explicit ModNode(std::unique_ptr<TermNode> term,
                   std::unique_ptr<FactorNode> factor) {
    term_ = std::move(term);
    factor_ = std::move(factor);
  }

  inline std::unique_ptr<TermNode>& get_term() { return term_; }

  inline std::unique_ptr<FactorNode>& get_factor() { return factor_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

 private:
  std::unique_ptr<TermNode> term_;
  std::unique_ptr<FactorNode> factor_;
};
}  // namespace ast
