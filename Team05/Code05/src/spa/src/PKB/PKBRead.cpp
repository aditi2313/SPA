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
  auto result_table =
      filter->FilterTable(std::move(relation_table_->modifies_table_.copy()));
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<AssignTable>> PKBRead::Assigns(
    IndexableFilterPtr<AssignData> filter) {
  auto result_table =
      filter->FilterTable(relation_table_->assign_table_.copy());
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<UsesTable>> PKBRead::Uses(
    IndexableFilterPtr<UsesData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->uses_table_.copy()));
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<FollowsTable>> PKBRead::Follows(
    IndexableFilterPtr<FollowsData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->follows_table_.copy()));
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<ParentTable>> PKBRead::Parent(
    IndexableFilterPtr<ParentData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->parent_table_.copy()));
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<CallsTable>> PKBRead::Calls(
    IndexableFilterPtr<CallsData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->calls_table_.copy()));
  return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<NextTable>> PKBRead::Next(
    IndexableFilterPtr<NextData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->next_table_.copy()));
  return create_result(std::move(result_table));
}

std::unordered_set<int> PKBRead::Affects(int s) {
  // bfs to find the variables that this stmt
  // affects --> assuming that this statement is an assign statement
  std::queue<int> frontier;
  std::unordered_set<int> visited;
  std::unordered_set<int> result;

  frontier.push(s);

  auto& modified = relation_table_->assign_table_.get_row(s);
  auto& modified_var = modified.get_variable();

  while (!frontier.empty()) {
    int curr = frontier.front();
    frontier.pop();
    auto& data = relation_table_->uses_table_.get_row(curr);
    if (visited.count(curr)) continue;
    if (data.get_variables().count(modified_var)) {
      result.insert(curr);
    }
    visited.insert(curr);
    // find th enext
    auto& next = relation_table_->next_table_.get_row(curr);
    for (auto& n : next.get_next_im_list()) {
      frontier.push(n);
    }
  }
  return result;
}

}  // namespace pkb
