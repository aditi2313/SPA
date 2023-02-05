#include "Evaluator.h"

namespace qps {
QueryResult Evaluator::EvaluateQuery(std::unique_ptr<Query> query) {
  QueryResult result;
  for (std::unique_ptr<Clause> &clause : query->get_clauses()) {
    QueryResult clause_result = clause->Evaluate(std::move(pkb_));
//    result.IntersectWith(clause_result);
  }
  return result;
}
}  // namespace qps
