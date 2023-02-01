#include "Clause.h"

namespace qps {
QueryResult ModifiesClause::Evaluate(pkb::PKBStub &pkb) {
  return pkb.ModifiesStub();
}
}