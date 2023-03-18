#include "PKBRead.h"

#include <cassert>
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

std::unique_ptr<PKBResult<ConditionTable>> PKBRead::Condition(
    IndexableFilterPtr<ConditionData> filter) {
  auto result_table = filter->FilterTable(relation_table_->condition_table_);
  return create_result(std::move(result_table));
}

std::unordered_set<int> PKBRead::Affects(int s) {
  // bfs to find the variables that this stmt

  std::unordered_set<int> result;

  if (!relation_table_->assign_.count(s)) {
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

  return result;
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
