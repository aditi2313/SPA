#include "ClauseEvaluator.h"

#include <utility>
#include <vector>

namespace qps {
// Returns true if there are results,
// false otherwise
bool ClauseEvaluator::EvaluateClause(
    ClausePtr &clause,
    Table &clause_table,
    EntitySet &LHS,
    EntitySet &RHS) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  return (arg1->IsSynonym() || arg2->IsSynonym())
         ? EvaluateSynonymClause(
          clause, clause_table, LHS, RHS)
         : EvaluateExactClause(clause, LHS, RHS);
}

// Handles these cases:
// (exact, exact)
// (_, exact)
// (exact, _)
// (_, _)
bool ClauseEvaluator::EvaluateExactClause(
    ClausePtr &clause,
    EntitySet &LHS,
    EntitySet &RHS) {
  AssertExactClauseArgs(
      clause->get_arg1(), clause->get_arg2());

  return QueryPKBForExactClause(
      clause, LHS, RHS);
}

// Handles these cases:
// (syn, exact | _)
// (exact | _, syn)
// (syn1, syn2) where syn1 != syn2
// (syn, syn) where syn == syn
bool ClauseEvaluator::EvaluateSynonymClause(
    ClausePtr &clause,
    Table &clause_table,
    EntitySet &LHS,
    EntitySet &RHS) {
  AssertSynonymClauseArgs(
      clause->get_arg1(), clause->get_arg2());

  EntitySet RHS_results;
  EntitySet LHS_results;
  Table::TwoSynonymRows rows;

  QueryPKBForSynonymClause(
      clause, LHS, RHS,
      LHS_results, RHS_results, rows);

  CreateClauseTable(
      clause, clause_table,
      LHS_results, RHS_results, rows);

  return !clause_table.Empty();
}

void ClauseEvaluator::AssertExactClauseArgs(
    ArgumentPtr &arg1, ArgumentPtr &arg2) {
  assert(!arg1->IsSynonym() && !arg2->IsSynonym());
}

bool ClauseEvaluator::QueryPKBForExactClause(ClausePtr &clause,
                                             EntitySet &LHS,
                                             EntitySet &RHS) {
  // Using Index instead of Filter because
  // the method should return early instead of
  // looking through and returning the whole table
  for (auto &index : LHS) {
    EntitySet results;
    clause->Index(index, pkb_, results);

    for (auto &entity : results) {
      if (RHS.count(entity)) return true;
    }
  }
  return false;
}

void ClauseEvaluator::AssertSynonymClauseArgs(
    ArgumentPtr &arg1, ArgumentPtr &arg2) {
  assert(arg1->IsSynonym() || arg2->IsSynonym());
}

void ClauseEvaluator::QueryPKBForSynonymClause(
    ClausePtr &clause,
    EntitySet &LHS,
    EntitySet &RHS,
    EntitySet &LHS_results,
    EntitySet &RHS_results,
    Table::TwoSynonymRows &rows) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  bool is_symmetric = *arg1 == *arg2;

  for (auto &index : LHS) {
    EntitySet results;
    if (arg2->IsWildcard()) {
      // Just index and return all
      clause->Index(index, pkb_, results);
    } else {
      // Is synonym or exact (int or ident), use filter
      is_symmetric
      ? clause->SymmetricFilter(index, pkb_, results)
      : clause->Filter(index, RHS, pkb_, results);
    }

    if (results.empty()) continue;

    LHS_results.insert(index);
    for (auto &entity : results) {
      RHS_results.insert(entity);
      rows.emplace_back(index, entity);
    }
  }
}

void ClauseEvaluator::CreateClauseTable(
    ClausePtr &clause,
    Table &clause_table,
    EntitySet &LHS_results,
    EntitySet &RHS_results,
    Table::TwoSynonymRows &rows) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  bool is_arg1_syn = arg1->IsSynonym();
  bool is_arg2_syn = arg2->IsSynonym();
  bool is_symmetric = *arg1 == *arg2;

  std::vector<SynonymName> columns;
  SynonymName arg1_syn_name, arg2_syn_name;
  if (is_arg1_syn)
    columns.emplace_back(
        arg1_syn_name = SynonymArg::get_full_name(arg1));

  if (is_arg2_syn)
    columns.emplace_back(
        arg2_syn_name = SynonymArg::get_full_name(arg2));

  clause_table = Table(columns);

  if (is_arg1_syn && is_arg2_syn && !is_symmetric) {
    clause_table.add_values(arg1_syn_name, arg2_syn_name, rows);
  } else if (is_arg1_syn) {
    clause_table.add_values(arg1_syn_name, LHS_results);
  } else {
    // arg2 is syn
    clause_table.add_values(arg2_syn_name, RHS_results);
  }
}
}  // namespace qps
