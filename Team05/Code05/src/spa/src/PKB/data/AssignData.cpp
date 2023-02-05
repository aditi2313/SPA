#include "AssignData.h"

#include <string>

namespace pkb {
    AssignData::AssignData(std::string variable, int line, std::unique_ptr<ast::ExprNode> expression) {
        variable_ = variable;
        line_ = line;
        expression_ = std::move(expression);
    }
} // namespace pkb