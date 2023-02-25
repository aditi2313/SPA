#pragma once

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"

namespace qps {
class ClauseEvaluator {
 public:
  ClauseEvaluator(pkb::PKBPtr &pkb)
      : pkb_(pkb) {}

  bool EvaluateClause(
      ClausePtr &clause,
      Table &clause_table,
      EntitySet &LHS,
      EntitySet &RHS);

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

 private:
  pkb::PKBPtr &pkb_;
};
}  // namespace qps
