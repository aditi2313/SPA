#pragma once

#include <memory>
#include <string>
#include <utility>

#include "models/AST/factor_node/FactorNode.h"
#include "Data.h"

namespace pkb {

class AssignData : public Data<Line> {
 public:
  AssignData(Var variable, Line line,
             std::unique_ptr<ast::ExprNode> expression);

  AssignData(const AssignData& other);

  bool TestExpression(const std::unique_ptr<ast::ExprNode>& other_node,
                      bool is_exact) {
    return is_exact ? expression_->DeepEquals(*other_node)
                    : expression_->PartialMatch(*other_node);
  }

  inline const std::string& get_variable() { return variable_; }

  AssignData& operator=(const AssignData& other) {
    variable_ = other.variable_;
    line_ = other.line_;
    expression_ = other.expression_->Copy();
    return *this;
  }

  friend bool operator==(const AssignData& LHS, const AssignData& RHS) {
    return LHS.expression_->DeepEquals(*RHS.expression_) &&
           LHS.variable_ == RHS.variable_ && LHS.line_ == RHS.line_;
  }

 private:
    Var variable_;
  std::unique_ptr<ast::ExprNode> expression_;
};
}  // namespace pkb
