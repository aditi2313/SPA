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

  bool TestExpression(const std::unique_ptr<ast::ExprNode>& other_node) {
    return other_node->DeepEquals(*expression_);
  }

  inline int get_line() { return line_; }

  inline const std::string& get_variable() { return variable_; }

 private:
  std::string variable_;
  int line_;
  std::unique_ptr<ast::ExprNode> expression_;
};
}  // namespace pkb
