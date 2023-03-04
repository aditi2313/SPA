#include <vector>

#include "QueryEvaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"
#include "ClauseEvaluator.h"

namespace qps {
extern MasterEntityFactory master_entity_factory_;

QueryResultPtr QueryEvaluator::EvaluateQuery(QueryPtr &query) {
  ClauseEvaluator clause_evaluator(pkb_);

  for (auto &clause : query->get_clauses()) {
    ArgumentPtr &arg1 = clause->get_arg1();
    ArgumentPtr &arg2 = clause->get_arg2();
    EntitySet LHS, RHS;
    Table clause_table;

    arg1->InitializeEntities(table_, pkb_, LHS);
    arg2->InitializeEntities(table_, pkb_, RHS);

    bool res = clause_evaluator.EvaluateClause(clause, clause_table, LHS, RHS);

    if (!res) {
      // Clause is false, can immediately return empty result.
      if (query->is_boolean_query()) {
        return std::make_unique<BooleanQueryResult>(false);
      } else {
        return std::make_unique<ListQueryResult>();
      }
    }

    if (!clause_table.Empty()) {
      table_ = TableJoiner::Join(table_, clause_table);
    }
  }

  if (query->is_boolean_query()) {
    return std::make_unique<BooleanQueryResult>(true);
  }

  // Join with selected synonyms at the end
  // instead of the beginning as a slight optimisation
  for (SynonymName syn : query->get_selected_synonyms()) {
    EntityName entity_name = query->get_declared_synonym_entity_name(
        syn);
    EntitySet initial_entities = master_entity_factory_.GetAllFromPKB(
        entity_name, pkb_);

    auto synonym_table = Table(syn, initial_entities);
    table_ = TableJoiner::Join(table_, synonym_table);
  }
  
  std::vector<std::vector<Entity>> results;
  table_.Select(query->get_selected_synonyms(), results);

  return std::make_unique<ListQueryResult>(
      results);
}
}  // namespace qps
