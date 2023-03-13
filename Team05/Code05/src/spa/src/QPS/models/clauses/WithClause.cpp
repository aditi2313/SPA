#include "WithClause.h"

namespace qps {
void WithClause::Preprocess(
    const pkb::PKBReadPtr &pkb,
    Table &query_table) {
  if (arg1_->IsSynonym()) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg1_.get());
    syn_arg->UpdateTableWithAttrValue(
        pkb, query_table);
  }

  if (arg2_->IsSynonym()) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg2_.get());
    syn_arg->UpdateTableWithAttrValue(
        pkb, query_table);
  }
}
}  // namespace qps
