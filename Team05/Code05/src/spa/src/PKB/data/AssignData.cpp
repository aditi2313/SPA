#include "AssignData.h"

#include <string>

namespace pkb {
AssignData::AssignData(std::string variable, int line,
                       std::unique_ptr<ast::ExprNode> expression)
                       : Data<int>(line) {
  variable_ = variable;
  expression_ = std::move(expression);
}

AssignData::AssignData(const AssignData& other)
    : Data<int>(other.line_) {
  variable_ = other.variable_;
  expression_ = other.expression_->Copy();
}
}  // namespace pkb
