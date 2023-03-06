#include "PKBRead.h"

#include <memory>

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
            filter->FilterTable(std::move(
                    relation_table_->follows_table_.copy()));
    return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<ParentTable>> PKBRead::Parent(
        IndexableFilterPtr<ParentData> filter) {
    auto result_table =
            filter->FilterTable(std::move(
                    relation_table_->parent_table_.copy()));
    return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<CallsTable>> PKBRead::Calls(
        IndexableFilterPtr<CallsData> filter) {
    auto result_table =
            filter->FilterTable(std::move(
                    relation_table_->calls_table_.copy()));
    return create_result(std::move(result_table));
}

std::unique_ptr<PKBResult<NextTable>> PKBRead::Next(
        IndexableFilterPtr<NextData> filter) {
    auto result_table =
            filter->FilterTable(std::move(
                    relation_table_->next_table_.copy()));
    return create_result(std::move(result_table));
}
}  // namespace pkb
