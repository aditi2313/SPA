#include "PKBRead.h"

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_set>

#include "tables/reader/DoubleIndexReader.h"
#include "common/exceptions/QPSExceptions.h"
#include "common/filter/filters/IndexFilter.h"

namespace pkb {
std::unique_ptr<ModifiesTable> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  auto result_table = filter->FilterTable(relation_table_->modifies_table_);
  return std::move(result_table);
}

std::unique_ptr<AssignTable> PKBRead::Assigns(
    IndexableFilterPtr<AssignData> filter) {
  auto result_table = filter->FilterTable(relation_table_->assign_table_);
  return std::move(result_table);
}

std::unique_ptr<UsesTable> PKBRead::Uses(
    IndexableFilterPtr<UsesData> filter) {
  auto result_table = filter->FilterTable(relation_table_->uses_table_);
  return std::move(result_table);
}

std::unique_ptr<FollowsTable> PKBRead::Follows(
    IndexableFilterPtr<FollowsData> filter) {
  auto result_table = filter->FilterTable(relation_table_->follows_table_);
  return std::move(result_table);
}

std::unique_ptr<ParentTable> PKBRead::Parent(
    IndexableFilterPtr<ParentData> filter) {
  auto result_table = filter->FilterTable(relation_table_->parent_table_);
  return std::move(result_table);
}

std::unique_ptr<CallsTable> PKBRead::Calls(
    IndexableFilterPtr<CallsData> filter) {
  auto result_table = filter->FilterTable(relation_table_->calls_table_);
  return std::move(result_table);
}

std::unique_ptr<NextTable> PKBRead::Next(
    IndexableFilterPtr<NextData> filter) {
  auto result_table = filter->FilterTable(relation_table_->next_table_);
  return std::move(result_table);
}

std::unique_ptr<ConditionTable> PKBRead::Condition(
    IndexableFilterPtr<ConditionData> filter) {
  auto result_table = filter->FilterTable(relation_table_->condition_table_);
  return std::move(result_table);
}

std::unordered_set<int> PKBRead::Affects(int s) {
  // Return cached result immediately if it has been
  // calculated before
  if (cache_->ExistsAffects(s)) {
    return cache_->GetAffects(s);
  }

  std::unordered_set<int> result;

  if (!relation_table_->assign_.count(s)) {
    cache_->WriteAffects(s, {});
    return {};
  }
  std::unordered_set<int> empt{};
  auto& table = relation_table_->next_table_;
  auto& modified = relation_table_->assign_table_.get_row(s);
  auto& modified_var = modified.get_variable();
  auto& n_im_l = table.exists(s) ? table.get_row(s).get_next_im_list() : empt;

  util::GraphSearch<int, std::unordered_set<int>>::BFS(
      [&](int& v) {
        if (!relation_table_->next_table_.exists(v))
          return std::unordered_set<int>{};
        auto& next = relation_table_->next_table_.get_row(v);
        return next.get_next_im_list();
      },
      n_im_l,
      [&](const int& curr) {
        if (relation_table_->uses_table_.exists(curr)) {
          auto& data = relation_table_->uses_table_.get_row(curr);
          // check that this assign stmt uses the variable
          if (data.get_variables().count(modified_var) &&
              relation_table_->assign_.count(curr)) {
            result.insert(curr);
          }
        }
        // if this stmt modifies the variable then dont do anything
        if (relation_table_->modifies_table_.exists(curr) &&
            !IsContainerStmt(curr)) {
          auto& data = relation_table_->modifies_table_.get_row(curr);
          if (data.get_variables().count(modified_var)) {
            return false;
          }
        }
        return true;
      });
  // Write to cache
  cache_->WriteAffects(s, result);
  return result;
}

std::unordered_set<int> PKBRead::AffectsT(int s) {
  // Return cached result immediately if it has been
  // calculated before
  if (cache_->ExistsAffectsT(s)) {
    return cache_->GetAffectsT(s);
  }

  std::unordered_set<int> affected_lines = Affects(s);
  std::unordered_set<int> affectedT_lines(affected_lines);

  std::queue<int> q;
  std::unordered_set<int> visited;

  // Initialize BFS queue
  for (auto& line : affected_lines) {
    q.push(line);
    visited.insert(line);
  }

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    affectedT_lines.insert(curr);  // Update result
    auto neighbors = Affects(curr);

    for (auto& neighbor : neighbors) {
      // Note: moving the visited check here helps to prevent
      // pushing many duplicate lines into the queue
      if (visited.count(neighbor)) continue;
      q.push(neighbor);
      visited.insert(neighbor);
    }
  }

  // Write back to cache
  cache_->WriteAffectsT(s, affectedT_lines);
  return affectedT_lines;
}

std::unordered_set<int> PKBRead::NextT(int v) {
  std::unordered_set<int> visited;
  std::queue<int> frontier;
  std::unordered_set<int> result;

  auto& next_table = relation_table_->next_table_;
  if (!relation_table_->next_table_.exists(v)) {
    return {};
  }
  auto& data = relation_table_->next_table_.get_row(v);

  util::GraphSearch<int, std::unordered_set<int>>::BFS(
      [&](int& curr) {
        if (!relation_table_->next_table_.exists(curr))
          return std::unordered_set<int>{};
        auto& child_data = relation_table_->next_table_.get_row(curr);
        return child_data.get_next_im_list();
      },
      data.get_next_im_list(),
      [&](const int& curr) {
        result.insert(curr);
        return true;
      });

  return result;
}
}  // namespace pkb
