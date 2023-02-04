#include "PKBRead.h"

#include <memory>

#include "common/Exceptions.h"

namespace pkb {
std::unique_ptr<PKBResult<ModifiesTable>> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  auto result_table =
      filter->FilterTable(relation_table_->modifies_table_.copy());
  return std::move(std::make_unique<PKBResult<ModifiesTable>>(
      std::move(relation_table_), std::move(result_table)));
}
}  // namespace pkb
