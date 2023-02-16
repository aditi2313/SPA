#include "PKBWrite.h"

#include <string>
#include <vector>

#include "common/Exceptions.h"

namespace pkb {

void PKBWrite::AddModifiesData(const int line,
                               const std::vector<std::string>& variables) {
  pkb_relation_table_->add_modifies_data(line, variables);
}

void PKBWrite::AddAssignData(std::string variable, int line,
                             std::unique_ptr<ast::ExprNode> expression) {
  pkb_relation_table_->add_assign_data(variable, line, std::move(expression));
}

void PKBWrite::AddUsesData(const int line,
                               const std::vector<std::string>& variable_names) {
    pkb_relation_table_->add_uses_data(line, variable_names);
}

void PKBWrite::AddFollowsData(const int line, const int follows) {
    pkb_relation_table_->add_follows_data(line, follows);
}

void PKBWrite::AddParentData(const int line, const int parent_line) {
    pkb_relation_table_->add_parent_data(line, parent_line);
}
}  // namespace pkb
