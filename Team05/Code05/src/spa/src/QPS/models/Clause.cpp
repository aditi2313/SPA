#include "Clause.h"

namespace qps {
models::QueryResult ModifiesClause::Evaluate(
    const std::unique_ptr<pkb::PKBRead>& pkb) {
  return pkb->Modifies(filter::ModifiesFilter());
}
}  // namespace qps
