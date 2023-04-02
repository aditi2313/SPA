#include "ClauseEvaluator.h"

#include <utility>
#include <vector>

namespace qps {
// Returns true if there are results,
// false otherwise
bool ClauseEvaluator::EvaluateClause(
    ClauseWrapper &state) {
  auto &clause = state.get_clause();
  return clause->has_synonym_arg()
         ? EvaluateSynonymClause(state)
         : EvaluateExactClause(state);
}

// Handles these cases:
// (exact, exact)
// (_, exact)
// (exact, _)
// (_, _)
bool ClauseEvaluator::EvaluateExactClause(
    ClauseWrapper &state) {
  auto &clause = state.get_clause();
  AssertExactClauseArgs(
      clause->get_arg1(), clause->get_arg2());

  return QueryPKBForExactClause(state);
}

// Handles these cases:
// (syn, exact | _)
// (exact | _, syn)
// (syn1, syn2) where syn1 != syn2
// (syn, syn) where syn == syn
bool ClauseEvaluator::EvaluateSynonymClause(
    ClauseWrapper &state) {
  auto &clause = state.get_clause();
  AssertSynonymClauseArgs(
      clause->get_arg1(), clause->get_arg2());

  Table::TwoSynonymRows rows;

  QueryPKBForSynonymClause(state, rows);

  CreateClauseTable(state, rows);

  auto &clause_table = state.get_clause_table();
  return !clause_table.Empty();
}

void ClauseEvaluator::AssertExactClauseArgs(
    ArgumentPtr &arg1, ArgumentPtr &arg2) {
  assert(!arg1->IsSynonym() && !arg2->IsSynonym());
}

bool ClauseEvaluator::QueryPKBForExactClause(
    ClauseWrapper &state) {
  auto &LHS = state.get_lhs();
  auto &RHS = state.get_rhs();
  auto &clause = state.get_clause();

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

void PopulateResults(Table::TwoSynonymRows &rows, EntitySet &LHS,
                     EntitySet &RHS) {
  for (auto &[l, r] : rows) {
    LHS.insert(l);
    RHS.insert(r);
  }
}

// Handles these cases:
// (syn, exact | _)
// (exact | _, syn)
// (syn1, syn2) where syn1 != syn2
// (syn, syn) where syn == syn
void ClauseEvaluator::QueryPKBForSynonymClause(
    ClauseWrapper &state,
    Table::TwoSynonymRows &rows) {
  auto &clause = state.get_clause();
  auto &LHS = state.get_lhs();
  auto &RHS = state.get_rhs();
  auto &LHS_results = state.get_lhs_results();
  auto &RHS_results = state.get_rhs_results();

  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  if (arg1->IsWildcard() || arg2->IsWildcard()) {
    arg2->IsWildcard() ? clause->WildcardFilterForLHS(LHS, pkb_, LHS_results)
                       : clause->WildcardFilterForRHS(LHS, RHS, pkb_,
                                                      RHS_results);
    return;
  }

  bool is_symmetric = *arg1 == *arg2;

  if (!is_symmetric) {
    clause->Filter(LHS, RHS, rows, pkb_);
    PopulateResults(rows, LHS_results, RHS_results);
    return;
  }

  // Evaluate double synonym symmetric case
  for (auto &index : LHS) {
    EntitySet results;
    clause->SymmetricFilter(index, pkb_, results);
    if (results.empty()) continue;
    for (auto &entity : results) {
      rows.emplace_back(index, entity);
    }
  }
}


void ClauseEvaluator::CreateClauseTable(
    ClauseWrapper &state,
    Table::TwoSynonymRows &rows) {
  auto &clause = state.get_clause();
  auto &clause_table = state.get_clause_table();
  auto &LHS_results = state.get_lhs_results();
  auto &RHS_results = state.get_rhs_results();

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
