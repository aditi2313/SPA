#pragma once

#include <memory>
#include <utility>

#include "models/AST/factor_node/FactorNode.h"

namespace pkb {

class AssignData {
 public:
  AssignData(std::string variable, int line,
             std::unique_ptr<ast::ExprNode> expression)
      : variable_(variable), line_(line) {
    expression_ = std::move(expression);
  }

  // TODO(Gab) Make test expression accept a Visitor for pattern matching
  bool TestExpression() { return true; }

  int get_line() { return line_; }

 private:
  std::string variable_;
  int line_;
  std::unique_ptr<ast::ExprNode> expression_;
};
}  // namespace pkb