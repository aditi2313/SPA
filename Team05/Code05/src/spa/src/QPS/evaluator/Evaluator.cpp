#include "Evaluator.h"

namespace qps {
pkb::PKBStub pkb;

QueryResult Evaluator::EvaluateQuery(Query query) {
  QueryResult result;
  for (Clause *clause : query.GetClauses()) {
    QueryResult clause_result = clause->Evaluate(pkb);
    result.Intersect(clause_result);
  }
  return result;
}
}  // namespace qps
