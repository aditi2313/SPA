#include "PKBRead.h"

#include <memory>
#include <queue>

#include "common/exceptions/QPSExceptions.h"

namespace pkb {

template <class T>
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

std::unordered_set<int> PKBRead::Affects(int s) {
  // bfs to find the variables that this stmt
  // affects --> assuming that this statement is an assign statement
  std::queue<int> frontier;
  std::unordered_set<int> visited;
  std::unordered_set<int> result;

  // if s is not an assign throw an exception
  if (!relation_table_->assign_.count(s)) {
    // todo(gab): throw custom exception
  }

  frontier.push(s);

  auto& modified = relation_table_->assign_table_.get_row(s);
  auto& modified_var = modified.get_variable();

  while (!frontier.empty()) {
    int curr = frontier.front();
    frontier.pop();
    if (visited.count(curr)) continue;
    if (relation_table_->uses_table_.exists(curr)) {
      auto& data = relation_table_->uses_table_.get_row(curr);
      // check that this assign stmt uses the variable
      if (data.get_variables().count(modified_var) &&
          relation_table_->assign_.count(curr)) {
        result.insert(curr);
      }
    }

    visited.insert(curr);
    // if this stmt modifies the variable then dont do anything
    if (relation_table_->modifies_table_.exists(curr) && curr != s &&
        IsAssignReadOrCall(curr)) {
      auto& data = relation_table_->modifies_table_.get_row(curr);
      if (data.get_variables().count(modified_var)) {
        continue;
      }
    }

    if (!relation_table_->next_table_.exists(curr)) continue;
    auto& next = relation_table_->next_table_.get_row(curr);
    for (auto& n : next.get_next_im_list()) {
      frontier.push(n);
    }
  }
  return result;
}

}  // namespace pkb
