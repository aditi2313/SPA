#include "WithClause.h"

namespace qps {
void WithClause::Preprocess(
    pkb::PKBReadPtr &pkb,
    Table &group_table) {
  if (arg1_->IsSynonym()) {
    AttrRefArg *attr_ref_arg = dynamic_cast<AttrRefArg *>(arg1_.get());
    attr_ref_arg->UpdateTableWithAttrValue(
        pkb, group_table);
  }

  if (arg2_->IsSynonym()) {
    AttrRefArg *attr_ref_arg = dynamic_cast<AttrRefArg *>(arg2_.get());
    attr_ref_arg->UpdateTableWithAttrValue(
        pkb, group_table);
  }
}
}  // namespace qps
