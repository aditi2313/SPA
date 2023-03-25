#pragma once

#include <utility>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"
#include "ClauseState.h"

namespace qps {
class ClauseEvaluator {
 public:
  explicit ClauseEvaluator(pkb::PKBReadPtr &pkb)
      : pkb_(pkb) {}

  bool EvaluateClause(
      ClauseState &state);

 private:
  // Clauses where neither argument is a synonym
  bool EvaluateExactClause(
      ClauseState &state);

  // Clauses where there is at least one synonym
  // in the argument
  bool EvaluateSynonymClause(
      ClauseState &state);

  // Helper methods for EvaluateExactClause
  void AssertExactClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  bool QueryPKBForExactClause(
      ClauseState &state);

  // Helper methods for EvaluateSynonymClause
  void AssertSynonymClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  void QueryPKBForSynonymClause(
      ClauseState &state,
      Table::TwoSynonymRows &rows);

  void CreateClauseTable(
      ClauseState &state,
      Table::TwoSynonymRows &rows);

  pkb::PKBReadPtr &pkb_;
};
}  // namespace qps
