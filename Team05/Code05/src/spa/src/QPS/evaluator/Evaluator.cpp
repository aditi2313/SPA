#include "Evaluator.h"

namespace qps {
QueryResult Evaluator::EvaluateQuery(Query query) {
  QueryResult result;
  for (Clause *clause : query.GetClauses()) {
    QueryResult clause_result = clause->Evaluate();
    result.Intersect(clause_result);
  }
  return result;
}
}  // namespace qps
