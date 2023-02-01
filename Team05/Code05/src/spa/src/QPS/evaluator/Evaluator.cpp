#include "Evaluator.h"

namespace qps {
QueryResult Evaluator::EvaluateQuery(Query query) {
  QueryResult result;
  for (std::unique_ptr<Clause> &clause : query.get_clauses()) {
    QueryResult clause_result = clause->Evaluate(std::move(pkb));
    result.Intersect(clause_result);
  }
  return result;
}
}  // namespace qps
