#pragma once
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>

#include "common/Utility.h"
#include "models/AST/TNode.h"
#include "models/AST/Token.h"

namespace ast {

class ExprNode : public TNode {
 public:
  virtual std::unique_ptr<ExprNode> Copy() = 0;
  virtual bool DeepEquals(const ExprNode&) = 0;
  virtual bool PartialMatch(const ExprNode&) = 0;
};

typedef std::unique_ptr<ExprNode> ExprNodePtr;
class OpNode : public ExprNode {
 public:
  OpNode(sp::Token operation, ExprNodePtr left, ExprNodePtr right)
      : operation_(operation) {
    left_ = std::move(left);
    right_ = std::move(right);
  }

  bool DeepEquals(const ExprNode& other) override {
    if (util::InstanceOf<OpNode>(other)) {
      const OpNode& o_v = dynamic_cast<const OpNode&>(other);
      return operation_ == o_v.operation_ && o_v.left_->DeepEquals(*left_) &&
              o_v.right_->DeepEquals(*right_);
    }
    return false;
  }

  bool PartialMatch(const ExprNode& other) override {
    if (DeepEquals(other)) return true;
    return left_->PartialMatch(other) || right_->PartialMatch(other);
  }

  ExprNodePtr Copy() override {
    auto res =
        std::make_unique<OpNode>(operation_, left_->Copy(), right_->Copy());
    return std::move(res);
  }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  ExprNodePtr& get_left() { return left_; }
  ExprNodePtr& get_right() { return right_; }

 private:
  sp::Token operation_;
  ExprNodePtr left_;
  ExprNodePtr right_;
};

class VarNode : public ExprNode {
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

  bool PartialMatch(ExprNode const& other) override {
    return DeepEquals(other);
  }

  inline std::string get_name() { return var_name_; }

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<VarNode>(var_name_);
  }

 private:
  std::string var_name_;
};

class ConstNode : public ExprNode {
 public:
  explicit ConstNode(int val) : val_(val) {}

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;

  inline int get_val() { return val_; }

  bool DeepEquals(ExprNode const& other) override {
    if (dynamic_cast<const ConstNode*>(&other)) {
      const ConstNode& o_v = dynamic_cast<const ConstNode&>(other);
      return o_v.val_ == val_;
    }
    return false;
  }

  bool PartialMatch(const ExprNode& other) override {
    return DeepEquals(other);
  }

  inline std::unique_ptr<ExprNode> Copy() override {
    return std::make_unique<ConstNode>(val_);
  }

 private:
  int val_;
};

}  // namespace ast
