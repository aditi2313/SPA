#include "PKBRead.h"

#include <memory>
#include <queue>
#include <unordered_set>

#include "common/exceptions/QPSExceptions.h"
#include "common/filter/filters/IndexFilter.h"

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

std::unordered_set<int> PKBRead::NextT(int v) {
  std::unordered_set<int> visited;
  std::queue<int> frontier;
  std::unordered_set<int> result;
  auto& next_table = relation_table_->next_table_;
  auto& data = relation_table_->next_table_.get_row(v);
  for (auto& l : data.get_next_im_list()) {
    frontier.push(l);
    result.insert(l);
  }
  while (!frontier.empty()) {
    int c = frontier.front();
    frontier.pop();
    if (visited.count(c)) continue;
    visited.insert(c);
    if (!relation_table_->next_table_.exists(c)) continue;
    auto& child_data = relation_table_->next_table_.get_row(c);
    for (auto& l : child_data.get_next_im_list()) {
      frontier.push(l);
      result.insert(l);
    }
  }
  return result;
}
}  // namespace pkb
