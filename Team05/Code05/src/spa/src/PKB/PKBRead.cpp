#include "PKBRead.h"

#include <memory>

#include "common/Exceptions.h"

namespace pkb {
IndexableTablePtr<ModifiesData> PKBRead::Modifies(
    IndexableFilterPtr<ModifiesData> filter) {
  return filter->FilterTable(relation_table_->modifies_table_.copy());
}
}  // namespace pkb
