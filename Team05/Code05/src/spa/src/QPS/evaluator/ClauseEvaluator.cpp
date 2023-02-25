#include "ClauseEvaluator.h"

namespace qps {

// Returns true if there are still results, false otherwise
bool ClauseEvaluator::EvaluateClause(
    QueryPtr &query,
    ClausePtr &clause,
    Table &clause_table,
    std::unique_ptr<pkb::PKBRead> &pkb) {

  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  // Fill with candidate values
  EntitySet LHS;
  EntitySet RHS;

  InitializeEntitiesFromArgument(query, arg1, pkb, clause->LHS(), LHS);
  InitializeEntitiesFromArgument(query, arg2, pkb, clause->RHS(), RHS);

  bool is_symmetric = arg1->IsSynonym() && (*arg1 == *arg2);
  bool is_lhs_syn = arg1->IsSynonym();
  bool is_rhs_syn = arg2->IsSynonym();

  Table table;

  // Takes care of duplicates
  EntitySet RHS_results;
  EntitySet LHS_results;

  // Query PKB with LHS possible values
  for (auto &index : LHS) {
    EntitySet results;
    if (arg2->IsWildcard()) {
      // Just index and return all
      results = clause->Index(index, pkb);
    } else {
      // Is synonym or exact (int or ident), need filter
      results = is_symmetric
                ? clause->SymmetricFilter(index, pkb)
                : clause->Filter(index, RHS, pkb);
    }

    if (results.empty()) continue;

    LHS_results.insert(index);
    for (auto &entity : results) {
      RHS_results.insert(entity);
    }
  }

  // Update list of possible values for arg1 and/or arg2
  // if they are synonyms
  UpdateSynonymEntityList(query, arg1, LHS_results);
  UpdateSynonymEntityList(query, arg2, RHS_results);

  return !RHS_results.empty();
}

}