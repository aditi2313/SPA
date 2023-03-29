#include <vector>

#include "QueryEvaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"
#include "ClauseEvaluator.h"
#include "ClauseOptimiser.h"
#include "ClauseWrapper.h"

namespace qps {
extern MasterEntityFactory master_entity_factory_;

QueryResultPtr QueryEvaluator::EvaluateQuery(QueryPtr &query) {
  // Requirement to clear cache for each query
  pkb_->ClearCache();

  auto &clauses = query->get_clauses();
  has_table_been_intialized_ = false;

  // Order of evaluation
  auto order = ClauseOptimiser::GroupClauses(clauses);

  for (auto &group : order) {
    for (auto &clause_index : group) {
      bool res = EvaluateClause(clauses.at(clause_index));

      if (!res) {
        // Clause is false, can immediately return empty result.
        return query->is_boolean_query()
               ? BooleanQueryResult::BuildFalse()
               : ListQueryResult::BuildEmpty();
      }
    }
  }

  return BuildResult(query);
}

bool QueryEvaluator::EvaluateClause(ClausePtr &clause) {
  clause->Preprocess(
      pkb_, table_, has_table_been_intialized_);

  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();
  EntitySet LHS, RHS;
  Table clause_table;

  arg1->InitializeEntities(table_, pkb_, LHS);
  arg2->InitializeEntities(table_, pkb_, RHS);

  ClauseWrapper clause_evaluator_state(
      clause, clause_table, LHS, RHS);

  bool res = clause_evaluator_.EvaluateClause(
      clause_evaluator_state);

  if (!clause_table.Empty()) {
    if (!has_table_been_intialized_) {
      table_ = clause_table;
      has_table_been_intialized_ = true;
    } else {
      table_ = TableJoiner::Join(table_, clause_table);
    }
    if (table_.Empty()) return false;
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
  if (AttrRef::is_attr_ref(elem)) {
    auto [syn_name, attr_name] = AttrRef::split_attr_ref(elem);
    EntityType entity_type = query->get_declared_synonym_entity_type(
        syn_name);
    AttrRefArg attr_ref_arg(syn_name, AttrRef::get_attr_type(attr_name));
    attr_ref_arg.set_entity_type(entity_type);
    attr_ref_arg.UpdateTableWithAttrValue(
        pkb_, table_, has_table_been_intialized_);
  } else {
    SynonymName syn_name = elem;
    EntityType entity_type = query->get_declared_synonym_entity_type(
        syn_name);
    EntitySet initial_entities = master_entity_factory_.GetAllFromPKB(
        entity_type, pkb_);

    auto synonym_table = Table(syn_name, initial_entities);
    if (!has_table_been_intialized_) {
      table_ = synonym_table;
      has_table_been_intialized_ = true;
    } else {
      table_ = TableJoiner::Join(table_, synonym_table);
    }
  }
}
}  // namespace qps
