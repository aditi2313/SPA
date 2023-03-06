#pragma once

#include <memory>
#include <string>
#include <utility>

#include "models/AST/factor_node/FactorNode.h"

namespace pkb {

class AssignData {
 public:
  AssignData(std::string variable, int line,
             std::unique_ptr<ast::ExprNode> expression);

  AssignData(const AssignData& other);

  bool TestExpression(const std::unique_ptr<ast::ExprNode>& other_node,
                      bool is_exact) {
    return is_exact ? expression_->DeepEquals(*other_node)
                    : expression_->PartialMatch(*other_node);
  }

  inline int get_index() { return line_; }

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
  std::string variable_;
  int line_;
  std::unique_ptr<ast::ExprNode> expression_;
};
}  // namespace pkb
