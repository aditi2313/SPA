#include "PKBWrite.h"

#include <functional>
#include <stack>
#include <string>
#include <unordered_set>

#include "common/exceptions/QPSExceptions.h"

namespace pkb {

using IntOrStringVariant = std::variant<int, std::string>;

template <class Data>
void ProcessIndexableTable(
    IndexableTable<Data>& table,
    std::function<void(Data&, IntOrStringVariant)> adding_function,
    std::function<std::unordered_set<IntOrStringVariant>(Data&)> get_children) {
  for (IntOrStringVariant id : table.get_indexes()) {
    Data& data_to_update = table.get_row(id);
    // use dfs to add all possible children
    std::stack<Data> frontier;
    frontier.push(data_to_update);
    while (!frontier.empty()) {
      auto v = frontier.top();
      frontier.pop();
      for (auto& child : get_children(v)) {
        adding_function(data_to_update, child);
        if (table.exists(child)) {
          frontier.push(table.get_row(child));
        }
      }
    }
  }
}

void PKBWrite::AddModifiesData(
    const std::variant<int, std::string> line,
    const std::unordered_set<std::string>& variables) {
  pkb_relation_table_->add_modifies_data(line, variables);
}

void PKBWrite::AddAssignData(std::string variable, int line,
                             std::unique_ptr<ast::ExprNode> expression) {
  pkb_relation_table_->add_assign_data(variable, line, std::move(expression));
}

void PKBWrite::AddUsesData(
    const std::variant<int, std::string> line,
    const std::unordered_set<std::string>& variable_names) {
  pkb_relation_table_->add_uses_data(line, variable_names);
}

void PKBWrite::AddFollowsData(const int line, const int follows) {
  pkb_relation_table_->add_follows_data(line, follows);
}

void PKBWrite::AddParentData(const int parent, const int child_line) {
  pkb_relation_table_->add_parent_data(parent, child_line);
}

void PKBWrite::AddCallsData(std::string caller, std::string callee) {
    pkb_relation_table_->add_calls_data(caller, callee);
}

void PKBWrite::AddNextData(int line, int next) {
    pkb_relation_table_->add_next_data(line, next);
}

void PKBWrite::ProcessFollows() {
  ProcessIndexableTable<FollowsData>(
      pkb_relation_table_->follows_table_,
      [](FollowsData& data, IntOrStringVariant v) {
          data.add_to_list(std::get<int>(v)); },
      [](FollowsData& data) {
        return std::unordered_set<IntOrStringVariant>{data.get_follows()};
      });
}

void PKBWrite::ProcessParent() {
  ProcessIndexableTable<ParentData>(
      pkb_relation_table_->parent_table_,
      [](ParentData& data, IntOrStringVariant v) {
          data.add_to_all_children(std::get<int>(v)); },
      [](ParentData& data) {
          std::unordered_set<int> direct_child_set = data.get_direct_children();
          std::unordered_set<IntOrStringVariant> variant_set;
          for (const auto& i : direct_child_set) {
              variant_set.emplace(i);
          }
          return variant_set;
      });
}

void PKBWrite::ProcessCalls() {
    ProcessIndexableTable<CallsData>(
            pkb_relation_table_->calls_table_,
            [](CallsData& data, IntOrStringVariant v) {
                data.add_to_total_calls(std::get<std::string>(v));},
            [](CallsData& data) {
                std::unordered_set<std::string> direct_calls_set = data.get_direct_calls();
                std::unordered_set<IntOrStringVariant> variant_set;
                for (const auto& i : direct_calls_set) {
                    variant_set.emplace(i);
                }
                return variant_set;;
            });
}
}  // namespace pkb
