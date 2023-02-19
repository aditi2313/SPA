#include "PKBWrite.h"

#include <functional>
#include <stack>
#include <string>
#include <unordered_set>

#include "common/Exceptions.h"

namespace pkb {

template <class Data>
void ProcessIndexableTable(
    IndexableTable<Data>& table,
    std::function<void(Data&, int)> adding_function,
    std::function<std::unordered_set<int>(Data&)> getter) {
  for (int id : table.get_indexes()) {
    Data& mod_data = table.get_row(id);
    // use dfs to add all possible children
    std::stack<Data> current;
    current.push(mod_data);
    while (!current.empty()) {
      auto v = current.top();
      current.pop();
      for (auto& child : getter(v)) {
        adding_function(mod_data, child);
        current.push(table.get_row(child));
      }
    }
  }
}

void PKBWrite::AddModifiesData(
    const int line, const std::unordered_set<std::string>& variables) {
  pkb_relation_table_->add_modifies_data(line, variables);
}

void PKBWrite::AddAssignData(std::string variable, int line,
                             std::unique_ptr<ast::ExprNode> expression) {
  pkb_relation_table_->add_assign_data(variable, line, std::move(expression));
}

void PKBWrite::AddUsesData(
    const int line, const std::unordered_set<std::string>& variable_names) {
  pkb_relation_table_->add_uses_data(line, variable_names);
}

void PKBWrite::AddFollowsData(const int line, const int follows) {
  pkb_relation_table_->add_follows_data(line, follows);
}

void PKBWrite::AddParentData(const int parent, const int child_line) {
  pkb_relation_table_->add_parent_data(parent, child_line);
}

void PKBWrite::ProcessFollows() {
  ProcessIndexableTable<FollowsData>(
      pkb_relation_table_->follows_table_,
      [](FollowsData& data, int v) { data.add_to_list(v); },
      [](FollowsData& data) {
        return std::unordered_set<int>{data.get_follows()};
      });
}

void PKBWrite::ProcessParent() {
  ProcessIndexableTable<ParentData>(
      pkb_relation_table_->parent_table_,
      [](ParentData& data, int v) { data.add_children(v); },
      [](ParentData& data) { return data.get_direct_children(); });
}

}  // namespace pkb
