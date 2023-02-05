#include "PKBRead.h"

#include <memory>

#include "common/Exceptions.h"

namespace pkb {
std::unique_ptr<PKBResult<ModifiesTable>> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  std::cout << "????\n";
  auto table_copy = relation_table_->modifies_table_.copy();
  auto result_table =
      filter->FilterTable(std::move(table_copy));
  auto result = std::make_unique<ModifiesTable>();
  return std::make_unique<PKBResult<ModifiesTable>>(
      std::move(relation_table_), std::move(result_table)
  );
}
}  // namespace pkb
