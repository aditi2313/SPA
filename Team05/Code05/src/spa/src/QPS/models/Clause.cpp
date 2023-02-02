#include "Clause.h"

namespace qps {
models::QueryResult ModifiesClause::Evaluate(
    const std::unique_ptr<pkb::PKBRead>& pkb) {
  // todo: setup arguement to evaluate the filter.
  throw new NotImplementedException();
}
}  // namespace qps
