#include "Evaluator.h"

namespace qps {
ListQueryResultPtr Evaluator::EvaluateQuery(std::unique_ptr<Query> &query) {
  Synonym selected_synonym = query->get_selected_synonyms().at(0);
  EntityId entity = query->get_synonym(selected_synonym);
  EntityPtrList all_entities = master_entity_factory_->GetAllFromPKB(
      entity, pkb_);
  ListQueryResultPtr result = std::make_unique<ListQueryResult>(all_entities);

  for (std::unique_ptr<Clause> &clause : query->get_clauses()) {
    QueryResultPtr clause_result = clause->Evaluate(
        master_entity_factory_, pkb_);

    if(clause_result->IsBoolean()) {
      BoolQueryResult* bool_query_result = dynamic_cast<BoolQueryResult*>(
          clause_result.get()
      );
      if(!bool_query_result->IsTrue()) {
        // Clause is false
        result->clear();
      }
    } else {
      ListQueryResult* list_query_result = dynamic_cast<ListQueryResult*>(
          clause_result.get());

      result->IntersectWith(*list_query_result);
    }
  }

  return result;
}
}  // namespace qps
