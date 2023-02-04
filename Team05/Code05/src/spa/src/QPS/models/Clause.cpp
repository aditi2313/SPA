#include "Clause.h"

namespace qps {
QueryResult ModifiesClause::Evaluate(std::unique_ptr<pkb::PKBRead> pkb) {
  // TODO(Gab): setup arguement to evaluate the filter.
  throw new NotImplementedException();
}
QueryResult PatternClause::Evaluate(std::unique_ptr<pkb::PKBRead> pkb) {
  // TODO(jl): replace with pattern method
  // return pkb->ModifiesStub();
  throw new NotImplementedException();
}

Clause::~Clause() = default;
}  // namespace qps
