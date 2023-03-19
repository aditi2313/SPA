#include "WithClause.h"

namespace qps {
void WithClause::Preprocess(
    pkb::PKBReadPtr &pkb,
    Table &query_table,
    bool &is_table_initialized) {
  if (arg1_->IsSynonym()) {
    AttrRefArg *attr_ref_arg = dynamic_cast<AttrRefArg *>(arg1_.get());
    attr_ref_arg->UpdateTableWithAttrValue(
        pkb, query_table, is_table_initialized);
  }

  if (arg2_->IsSynonym()) {
    AttrRefArg *attr_ref_arg = dynamic_cast<AttrRefArg *>(arg2_.get());
    attr_ref_arg->UpdateTableWithAttrValue(
        pkb, query_table, is_table_initialized);
  }
}
}  // namespace qps
