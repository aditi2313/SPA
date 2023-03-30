#include "PKBWrite.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>

#include "common/exceptions/QPSExceptions.h"

namespace pkb {

template <class Data, class Table = IndexableTable<Data>, class K = Key>
void ProcessIndexableTable(
    Table& table, std::function<void(Data&, K)> adding_function,
    std::unordered_set<K>& indexes,
    std::function<std::unordered_set<K>(Data&)> get_children) {
  for (K id : indexes) {
    if (!table.exists(id)) continue;
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

template <class Data, class Table = IndexableTable<Data>, class K = Key>
void ProcessIndexableTableInt(
    Table& table,
    std::unordered_set<K>& indexes,
    std::function<LineSet(Data&)> get_children) {
    std::vector<K> v(indexes.size());
    std::copy(indexes.begin(), indexes.end(), v.begin());
    std::sort(v.begin(), v.end());
    for (int i = v.size() - 1; i >= 0; --i) {
        auto id = v.at(i);
        if (!table.exists(id)) continue;
        Data& data_to_update = table.get_row(id);
        for (auto& child : get_children(data_to_update)) {
            if (!table.exists(child)) continue;
            data_to_update.AddData(table.get_row(child));
        }
    }
}

void PKBWrite::AddModifiesData(
    const Key line,
    const VarSet& variables) {
  if (variables.empty()) {
    return;
  }
  pkb_relation_table_->add_modifies_data(line, variables);
}

void PKBWrite::AddAssignData(std::string variable, int line,
                             std::unique_ptr<ast::ExprNode> expression) {
  pkb_relation_table_->add_assign_data(variable, line, std::move(expression));
}

void PKBWrite::AddUsesData(
    const Key line,
    const VarSet& variable_names) {
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

void PKBWrite::AddConditionData(
    const Key line,
    const VarSet& variable_names) {
  pkb_relation_table_->add_condition_data(line, variable_names);
}

void PKBWrite::ProcessFollows() {
  ProcessIndexableTableInt<FollowsData, FollowsDTable>(
      pkb_relation_table_->follows_d_table_,
      pkb_relation_table_->stmts_,
      [&](FollowsData& data) {
        return LineSet{data.get_follows()};
      });
}

void PKBWrite::ProcessParent() {
  ProcessIndexableTableInt<ParentData>(
      pkb_relation_table_->parent_d_table_,
      pkb_relation_table_->stmts_,
      [&](ParentData& data) {
          return data.get_direct_children();
      });
}

void PKBWrite::ProcessCalls() {
  ProcessIndexableTable<CallsData, CallsDTable, std::string>(
      pkb_relation_table_->calls_d_table_,
      [](CallsData& data, std::string v) {
        data.add_to_total_calls(v);
      },
      pkb_relation_table_->procedures_,
      [](CallsData& data) {
        return data.get_direct_calls();
      });
}
}  // namespace pkb
