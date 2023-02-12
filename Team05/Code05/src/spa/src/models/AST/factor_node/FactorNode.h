#pragma once
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>

#include "models/AST/TNode.h"

namespace ast {

class ExprNode : public TNode {
 public:
  virtual std::unique_ptr<ExprNode> Copy() = 0;
  virtual bool DeepEquals(const ExprNode&) = 0;
};

class TermNode : public ExprNode {
 public:
  virtual std::unique_ptr<TermNode> CopyTerm() = 0;
};

class FactorNode : public TermNode {
 public:
  virtual std::unique_ptr<FactorNode> CopyFactor() = 0;
};

class VarNode : public FactorNode {
 public:
  explicit VarNode(std::string var_name) : var_name_(var_name) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const VarNode*>(&other)) {
      const VarNode& o_v = dynamic_cast<const VarNode&>(other);
      return var_name_ == o_v.var_name_;
    }
    return false;
  }

  inline std::string get_name() { return var_name_; }

  inline std::unique_ptr<FactorNode> CopyFactor() override {
    return std::make_unique<VarNode>(var_name_);
  }

  inline std::unique_ptr<TermNode> CopyTerm() override {
    return CopyFactor();
  }

  inline std::unique_ptr<ExprNode> Copy() override { return CopyFactor(); }

 private:
  std::string var_name_;
};

class ConstNode : public FactorNode {
 public:
  explicit ConstNode(int val) : val_(val) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  inline int get_val() { return val_; }

  inline std::unique_ptr<FactorNode> CopyFactor() override {
    return std::make_unique<ConstNode>(val_);
  }

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const ConstNode*>(&other)) {
      const ConstNode& o_v = dynamic_cast<const ConstNode&>(other);
      return o_v.val_ == val_;
    }
    return false;
  }

  inline std::unique_ptr<TermNode> CopyTerm() override { return CopyFactor(); }

  inline std::unique_ptr<ExprNode> Copy() override { return CopyFactor(); }

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

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<PlusNode>(expr_->Copy(), term_->CopyTerm());
  }

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const PlusNode*>(&other)) {
      const PlusNode& o_v = dynamic_cast<const PlusNode&>(other);
      return o_v.expr_->DeepEquals(*expr_) && o_v.term_->DeepEquals(*term_);
    }
    return false;
  }

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

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<MinusNode>(expr_->Copy(), term_->CopyTerm());
  }

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const MinusNode*>(&other)) {
      const MinusNode& o_v = dynamic_cast<const MinusNode&>(other);
      return o_v.expr_->DeepEquals(*expr_) && o_v.term_->DeepEquals(*term_);
    }
    return false;
  }

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

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const TimesNode*>(&other)) {
      const TimesNode& o_v = dynamic_cast<const TimesNode&>(other);
      return o_v.term_->DeepEquals(*term_) && o_v.factor_->DeepEquals(*factor_);
    }
    return false;
  }

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<TimesNode>(term_->CopyTerm(),
                                       factor_->CopyFactor());
  }

  inline std::unique_ptr<TermNode> CopyTerm() override {
    return std::make_unique<TimesNode>(term_->CopyTerm(),
                                       factor_->CopyFactor());
  }

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

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<DivNode>(term_->CopyTerm(), factor_->CopyFactor());
  }

  inline std::unique_ptr<TermNode> CopyTerm() override {
    return std::make_unique<DivNode>(term_->CopyTerm(), factor_->CopyFactor());
  }

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const DivNode*>(&other)) {
      const DivNode& o_v = dynamic_cast<const DivNode&>(other);
      return o_v.term_->DeepEquals(*term_) && o_v.factor_->DeepEquals(*factor_);
    }
    return false;
  }

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

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const ModNode*>(&other)) {
      const ModNode& o_v = dynamic_cast<const ModNode&>(other);
      return o_v.term_->DeepEquals(*term_) && o_v.factor_->DeepEquals(*factor_);
    }
    return false;
  }

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<ModNode>(term_->CopyTerm(), factor_->CopyFactor());
  }

  inline std::unique_ptr<TermNode> CopyTerm() override {
    return std::make_unique<ModNode>(term_->CopyTerm(), factor_->CopyFactor());
  }

 private:
  std::unique_ptr<TermNode> term_;
  std::unique_ptr<FactorNode> factor_;
};
}  // namespace ast
