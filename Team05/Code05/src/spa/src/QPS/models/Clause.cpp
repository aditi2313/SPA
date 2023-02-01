#include "Clause.h"

namespace qps {
QueryResult ModifiesClause::Evaluate(const pkb::PKBStub &pkb) {
  return pkb.ModifiesStub();
}
}  // namespace qps
