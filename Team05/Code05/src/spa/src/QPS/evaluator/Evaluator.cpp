#include "Evaluator.h"

namespace qps {
models::QueryResult Evaluator::EvaluateQuery(Query query) {
  models::QueryResult result;
  for (std::unique_ptr<Clause> &clause : query.get_clauses()) {
    models::QueryResult clause_result = clause->Evaluate(std::move(pkb));
    result.IntersectWith(clause_result);
  }
  return result;
}
}  // namespace qps
