#include "ClauseEvaluator.h"

namespace qps {

// Returns true if there are still results, false otherwise
bool ClauseEvaluator::EvaluateClause(
    ClausePtr &clause,
    Table &clause_table,
    EntitySet &LHS,
    EntitySet &RHS) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  if (arg1->IsSynonym() || arg2->IsSynonym()) {
    auto table = EvaluateSynonymClause(clause, LHS, RHS);
    clause_table = table;
    return !table.Empty();
  } else {
    return EvaluateExactClause(clause, LHS, RHS);
  }
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
  /* ============ ASSERTION CHECK ============= */
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  assert(!arg1->IsSynonym() && !arg2->IsSynonym());
  /* ============= END OF CHECK =============== */


  // Using Index instead of Filter because
  // I want the method to return early instead of
  // looking through and returning the whole table
  for (auto &index : LHS) {
    EntitySet results;
    results = clause->Index(index, pkb_);

    for (auto &entity : results) {
      if (RHS.count(entity)) return true;
    }
  }
  return false;
}

// Handles these cases:
// (syn, exact | _)
// (exact | _, syn)
// (syn1, syn2) where syn1 != syn2
// (syn, syn) where syn == syn
Table ClauseEvaluator::EvaluateSynonymClause(
    ClausePtr &clause,
    EntitySet &LHS,
    EntitySet &RHS) {
  /* ============ ASSERTION CHECK ============= */
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  bool is_arg1_syn = arg1->IsSynonym();
  bool is_arg2_syn = arg2->IsSynonym();

  assert(is_arg1_syn || is_arg2_syn);
  /* ============= END OF CHECK =============== */

  bool is_symmetric = *arg1 == *arg2;

  EntitySet RHS_results;
  EntitySet LHS_results;
  std::vector<std::pair<Entity, Entity>> rows;

  /* === Query PKB with LHS possible values === */
  for (auto &index : LHS) {
    EntitySet results;
    if (arg2->IsWildcard()) {
      // Just index and return all
      results = clause->Index(index, pkb_);
    } else {
      // Is synonym or exact (int or ident), use filter
      results = is_symmetric
                ? clause->SymmetricFilter(index, pkb_)
                : clause->Filter(index, RHS, pkb_);
    }

    if (results.empty()) continue;

    LHS_results.insert(index);
    for (auto &entity : results) {
      RHS_results.insert(entity);
      rows.emplace_back(index, entity);
    }
  }

  /* ============== Get new table ============== */
  std::vector<SynonymName> columns;
  SynonymName arg1_syn_name, arg2_syn_name;
  if (is_arg1_syn)
    columns.push_back(
        arg1_syn_name = SynonymArg::get_syn_name(arg1));

  if (is_arg2_syn)
    columns.push_back(
        arg2_syn_name = SynonymArg::get_syn_name(arg2));

  Table new_table(columns);

  if (is_arg1_syn && is_arg2_syn && !is_symmetric) {
    for (auto &[lhs, rhs] : rows) {
      Table::Row new_row;
      new_row.push_back({arg1_syn_name, lhs});
      new_row.push_back({arg2_syn_name, rhs});
      new_table.AddRow(new_row);
    }
  } else if (is_arg1_syn) {
    for (auto &lhs : LHS_results) {
      Table::Row new_row;
      new_row.push_back({arg1_syn_name, lhs});
      new_table.AddRow(new_row);
    }
  } else {
    // arg2 is syn
    for (auto &rhs : RHS_results) {
      Table::Row new_row;
      new_row.push_back({arg2_syn_name, rhs});
      new_table.AddRow(new_row);
    }
  }

  return new_table;
}
}