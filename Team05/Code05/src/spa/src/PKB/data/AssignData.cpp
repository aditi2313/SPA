#include "AssignData.h"

#include <string>

namespace pkb {
AssignData::AssignData(std::string variable, int line,
                       std::unique_ptr<ast::ExprNode> expression) {
  variable_ = variable;
  line_ = line;
  expression_ = std::move(expression);
}

AssignData::AssignData(const AssignData& other) {
  variable_ = other.variable_;
  line_ = other.line_;
  expression_ = other.expression_->Copy();
}
}  // namespace pkb
