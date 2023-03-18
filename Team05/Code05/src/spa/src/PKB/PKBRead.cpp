#include "PKBRead.h"

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_set>

#include "common/exceptions/QPSExceptions.h"
#include "common/filter/filters/IndexFilter.h"

namespace pkb {

template<class T>
std::unique_ptr<PKBResult<T>> create_result(std::unique_ptr<T> result) {
  return std::make_unique<PKBResult<T>>(std::move(result));
}

std::unique_ptr<PKBResult<ModifiesTable>> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  auto result_table = filter->FilterTable(relation_table_->modifies_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<AssignTable>> PKBRead::Assigns(
    IndexableFilterPtr<AssignData> filter) {
  auto result_table = filter->FilterTable(relation_table_->assign_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<UsesTable>> PKBRead::Uses(
    IndexableFilterPtr<UsesData> filter) {
  auto result_table = filter->FilterTable(relation_table_->uses_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<FollowsTable>> PKBRead::Follows(
    IndexableFilterPtr<FollowsData> filter) {
  auto result_table = filter->FilterTable(relation_table_->follows_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<ParentTable>> PKBRead::Parent(
    IndexableFilterPtr<ParentData> filter) {
  auto result_table = filter->FilterTable(relation_table_->parent_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<CallsTable>> PKBRead::Calls(
    IndexableFilterPtr<CallsData> filter) {
  auto result_table = filter->FilterTable(relation_table_->calls_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<NextTable>> PKBRead::Next(
    IndexableFilterPtr<NextData> filter) {
  auto result_table = filter->FilterTable(relation_table_->next_table_);
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<ConditionTable>> PKBRead::Condition(
    IndexableFilterPtr<ConditionData> filter) {
  auto result_table = filter->FilterTable(relation_table_->condition_table_);
  return create_result(std::move(result_table));
}

std::unordered_set<int> PKBRead::Affects(int s) {
  // Return cached result immediately if it has been
  // calculated before
  if (cache_.exists(s)) {
    return cache_.GetAffects(s).get_affected_lines();
  }

  // bfs to find the variables that this stmt
  std::queue<int> frontier;
  std::unordered_set<int> visited;
  std::unordered_set<int> result;

  if (!relation_table_->assign_.count(s)) {
    return {};
  }

  frontier.push(s);

  auto &modified = relation_table_->assign_table_.get_row(s);
  auto &modified_var = modified.get_variable();

  while (!frontier.empty()) {
    int curr = frontier.front();
    frontier.pop();
    if (visited.count(curr)) continue;
    if (relation_table_->uses_table_.exists(curr)) {
      auto &data = relation_table_->uses_table_.get_row(curr);
      // check that this assign stmt uses the variable
      if (data.get_variables().count(modified_var) &&
          relation_table_->assign_.count(curr)) {
        result.insert(curr);
      }
    }

    visited.insert(curr);
    // if this stmt modifies the variable then dont do anything
    if (relation_table_->modifies_table_.exists(curr) && curr != s &&
        !IsContainerStmt(curr)) {
      auto &data = relation_table_->modifies_table_.get_row(curr);
      if (data.get_variables().count(modified_var)) {
        continue;
      }
    }

    if (!relation_table_->next_table_.exists(curr)) continue;
    auto &next = relation_table_->next_table_.get_row(curr);
    for (auto &n : next.get_next_im_list()) {
      frontier.push(n);
    }
  }
  // Write to cache
  cache_.WriteAffects(s, result);

  return result;
}

std::unordered_set<int> PKBRead::AffectsT(int s) {
  std::unordered_set<int> affects_lines = Affects(s);
  // Named it affects_t_lines instead of all_affected_lines
  // because affects_t is not really semantically equivalent
  // to all_affected_lines
  std::unordered_set<int> affects_t_lines(affects_lines);

  std::queue<int> q;
  std::unordered_set<int> visited;

  // Initialize BFS queue
  for (auto &line : affects_lines) {
    q.push(line);
    visited.insert(line);
  }

  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    affects_t_lines.insert(curr);  // Update result
    auto neighbors = Affects(curr);

    for (auto &neighbor : neighbors) {
      // Note: moving the visited check here helps to prevent
      // pushing many duplicate lines into the queue
      if (visited.count(neighbor)) continue;
      q.push(neighbor);
      visited.insert(neighbor);
    }
  }

  return affects_t_lines;
}

std::unordered_set<int> PKBRead::NextT(int v) {
  std::unordered_set<int> visited;
  std::queue<int> frontier;
  std::unordered_set<int> result;
  auto &next_table = relation_table_->next_table_;
  if (!relation_table_->next_table_.exists(v)) {
    return {};
  }
  auto &data = relation_table_->next_table_.get_row(v);
  for (auto &l : data.get_next_im_list()) {
    frontier.push(l);
    result.insert(l);
  }
  while (!frontier.empty()) {
    int c = frontier.front();
    frontier.pop();
    if (visited.count(c)) continue;
    visited.insert(c);
    if (!relation_table_->next_table_.exists(c)) continue;
    auto &child_data = relation_table_->next_table_.get_row(c);
    for (auto &l : child_data.get_next_im_list()) {
      frontier.push(l);
      result.insert(l);
    }
  }
  return result;
}
}  // namespace pkb
