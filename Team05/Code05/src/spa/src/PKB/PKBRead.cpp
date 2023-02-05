#include "PKBRead.h"

#include <memory>

#include "common/Exceptions.h"

namespace pkb {

template<class T>
std::unique_ptr<PKBResult<T>> create_result(
    std::unique_ptr<PKBRelationTable> rel_table, std::unique_ptr<T> result) {
  return std::move(
      std::make_unique<PKBResult<T>>(std::move(rel_table), std::move(result)));
}

std::unique_ptr<PKBResult<ModifiesTable>> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  auto result_table =
      filter->FilterTable(std::move(relation_table_->modifies_table_.copy()));
  return create_result(
      std::move(relation_table_), std::move(result_table));
}

std::unique_ptr<PKBResult<AssignTable>> PKBRead::Assigns(
    IndexableFilterPtr<std::shared_ptr<AssignData>> filter) {
  auto result_table =
      filter->FilterTable(relation_table_->assign_table_.copy());
  return create_result(std::move(relation_table_), std::move(result_table));
}
}  // namespace pkb