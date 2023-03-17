#include <vector>

#include "QueryEvaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"
#include "ClauseEvaluator.h"
#include "ClauseOptimiser.h"

namespace qps {
extern MasterEntityFactory master_entity_factory_;

QueryResultPtr QueryEvaluator::EvaluateQuery(QueryPtr &query) {
  auto &clauses = query->get_clauses();

  // Order of evaluation
  auto order = ClauseOptimiser::GroupClauses(clauses);

  for (auto &group : order) {
    for (auto &clause_index : group) {
      bool res = EvaluateClause(clauses.at(clause_index));

      if (!res) {
        // Clause is false, can immediately return empty result.
        if (query->is_boolean_query()) {
          return std::make_unique<BooleanQueryResult>(false);
        } else {
          return std::make_unique<ListQueryResult>();
        }
      }
    }
  }

  return BuildResult(query);
}

bool QueryEvaluator::EvaluateClause(ClausePtr &clause) {
  clause->Preprocess(pkb_, table_);

  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  EntitySet LHS, RHS;
  Table clause_table;

  arg1->InitializeEntities(table_, pkb_, LHS);
  arg2->InitializeEntities(table_, pkb_, RHS);

  bool res = clause_evaluator_.EvaluateClause(
      clause, clause_table, LHS, RHS);

  if (!clause_table.Empty()) {
    table_ = TableJoiner::Join(table_, clause_table);
  }

  return res;
}

QueryResultPtr QueryEvaluator::BuildResult(QueryPtr &query) {
  if (query->is_boolean_query()) {
    return std::make_unique<BooleanQueryResult>(true);
  }

  // Join with selected synonyms at the end
  // instead of the beginning as a slight optimisation
  for (Elem elem : query->get_selected_elems()) {
    if (table_.HasColumn(elem)) continue;
    UpdateTableWithElem(query, elem);
  }

  std::vector<std::vector<Entity>> results;
  table_.Select(query->get_selected_elems(), results);

  return std::make_unique<ListQueryResult>(
      results);
}

void QueryEvaluator::UpdateTableWithElem(
    QueryPtr &query, Elem elem) {
  if (PQL::is_attr_ref(elem)) {
    auto [syn_name, attr_name] = PQL::split_attr_ref(elem);
    EntityName entity_name = query->get_declared_synonym_entity_name(
        syn_name);
    SynonymArg syn_arg(syn_name);
    syn_arg.set_entity_name(entity_name);
    syn_arg.set_attr_name(attr_name);
    syn_arg.UpdateTableWithAttrValue(pkb_, table_);
  } else {
    SynonymName syn_name = elem;
    EntityName entity_name = query->get_declared_synonym_entity_name(
        syn_name);
    EntitySet initial_entities = master_entity_factory_.GetAllFromPKB(
        entity_name, pkb_);

    auto synonym_table = Table(syn_name, initial_entities);
    table_ = TableJoiner::Join(table_, synonym_table);
  }
}
}  // namespace qps
