#include "Evaluator.h"

namespace qps {
QueryResult Evaluator::EvaluateQuery(std::unique_ptr<Query> query) {
  QueryResult result;
  bool is_result_initialized = false;
  for (std::unique_ptr<Clause> &clause : query->get_clauses()) {
    QueryResult clause_result = clause->Evaluate(pkb_);

    if (!is_result_initialized) {
      result = clause_result;
    } else {
      result.IntersectWith(clause_result);
    }

    is_result_initialized = true;
  }

  return result;
}
}  // namespace qps
