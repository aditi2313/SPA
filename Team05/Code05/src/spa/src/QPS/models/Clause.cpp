#include "Clause.h"

namespace qps {
QueryResult ModifiesClause::Evaluate(std::unique_ptr<pkb::PKBStub> pkb) {
  return pkb->ModifiesStub();
}
}  // namespace qps
