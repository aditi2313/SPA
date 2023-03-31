#include "AssignData.h"

#include <string>

namespace pkb {
AssignData::AssignData(Var variable, Line line,
                       std::unique_ptr<ast::ExprNode> expression)
                       : Data<Line>(line) {
  variable_ = variable;
  expression_ = std::move(expression);
}

AssignData::AssignData(const AssignData& other)
    : Data<Line>(other.line_) {
  variable_ = other.variable_;
  expression_ = other.expression_->Copy();
}
}  // namespace pkb
