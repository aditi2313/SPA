#include "Clause.h"

namespace qps {
QueryResult ModifiesClause::Evaluate(std::unique_ptr<pkb::PKBStub> pkb) {
  return pkb->ModifiesStub();
}
QueryResult PatternClause::Evaluate(std::unique_ptr<pkb::PKBStub> pkb) {
  // TODO(jl): replace with pattern method
  return pkb->ModifiesStub();
}

Clause::~Clause() = default;
}  // namespace qps
