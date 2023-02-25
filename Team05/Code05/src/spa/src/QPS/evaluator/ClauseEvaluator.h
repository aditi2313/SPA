#pragma once

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"

namespace qps {
class ClauseEvaluator {
 public:
  explicit ClauseEvaluator(pkb::PKBReadPtr &pkb)
      : pkb_(pkb) {}

  bool EvaluateClause(
      ClausePtr &clause,
      Table &clause_table,
      EntitySet &LHS,
      EntitySet &RHS);

 private:
  // Clauses where neither argument is a synonym
  bool EvaluateExactClause(
      ClausePtr &clause,
      EntitySet &LHS,
      EntitySet &RHS);

  // Clauses where there is at least one synonym
  // in the argument
  Table EvaluateSynonymClause(
      ClausePtr &clause,
      EntitySet &LHS,
      EntitySet &RHS);

  pkb::PKBReadPtr &pkb_;
};
}  // namespace qps
