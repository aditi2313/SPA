#pragma once

#include <utility>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"
#include "ClauseWrapper.h"

namespace qps {
class ClauseEvaluator {
 public:
  explicit ClauseEvaluator(pkb::PKBReadPtr &pkb)
      : pkb_(pkb) {}

  bool EvaluateClause(
      ClauseWrapper &state);

 private:
  // Clauses where neither argument is a synonym
  bool EvaluateExactClause(
      ClauseWrapper &state);

  // Clauses where there is at least one synonym
  // in the argument
  bool EvaluateSynonymClause(
      ClauseWrapper &state);

  // Helper methods for EvaluateExactClause
  void AssertExactClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  bool QueryPKBForExactClause(
      ClauseWrapper &state);

  // Helper methods for EvaluateSynonymClause
  void AssertSynonymClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  void QueryPKBForSynonymClause(
      ClauseWrapper &state,
      Table::TwoSynonymRows &rows);

  void CreateClauseTable(
      ClauseWrapper &state,
      Table::TwoSynonymRows &rows);

  pkb::PKBReadPtr &pkb_;
};
}  // namespace qps
