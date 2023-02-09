#include "Evaluator.h"

namespace qps {
QueryResultPtr Evaluator::EvaluateQuery(std::unique_ptr<Query> &query) {
  Synonym selected_synonym = query->get_selected_synonyms().at(0);
  EntityId entity = query->get_synonym(selected_synonym);
  EntityPtrList all_entities = master_entity_factory_->GetAllFromPKB(
      entity, pkb_);
  QueryResultPtr result = std::make_unique<QueryResult>(all_entities);

  for (std::unique_ptr<Clause> &clause : query->get_clauses()) {
    if (clause->IsExact()) {
      // CLAUSE is type that returns only TRUE or FALSE
      // TODO(JL): evaluateExactClause()
      // if TRUE, continue, if FALSE, clear results
      continue;
    }

    // Has one synonym
    // TODO(JL): if CLAUSE has no relation with the selected synonym
    // then just continue

    QueryResultPtr clause_result = clause->Evaluate(
        master_entity_factory_, pkb_);
    result->IntersectWith(clause_result);
  }

  return result;
}
}  // namespace qps
