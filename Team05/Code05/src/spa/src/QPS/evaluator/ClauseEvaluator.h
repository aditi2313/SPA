#pragma once

#include <utility>
#include <vector>

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
  using TwoSynonymRows = std::vector<std::pair<Entity, Entity>>;

  // Clauses where neither argument is a synonym
  bool EvaluateExactClause(
      ClausePtr &clause,
      EntitySet &LHS,
      EntitySet &RHS);

  // Clauses where there is at least one synonym
  // in the argument
  bool EvaluateSynonymClause(
      ClausePtr &clause,
      Table &clause_table,
      EntitySet &LHS,
      EntitySet &RHS);

  // Helper methods for EvaluateExactClause
  void AssertExactClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  bool QueryPKBForExactClause(
      ClausePtr &clause,
      EntitySet &LHS,
      EntitySet &RHS);

  // Helper methods for EvaluateSynonymClause
  void AssertSynonymClauseArgs(
      ArgumentPtr &arg1, ArgumentPtr &arg2);

  void QueryPKBForSynonymClause(
      ClausePtr &clause,
      EntitySet &LHS,
      EntitySet &RHS,
      EntitySet &LHS_results,
      EntitySet &RHS_results,
      TwoSynonymRows &rows);

  void CreateClauseTable(
      ClausePtr &clause,
      Table &clause_table,
      EntitySet &LHS_results,
      EntitySet &RHS_results,
      TwoSynonymRows &rows);

  pkb::PKBReadPtr &pkb_;
};
}  // namespace qps
