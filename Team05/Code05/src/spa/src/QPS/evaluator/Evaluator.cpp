#include "Evaluator.h"

namespace qps {
QueryResultPtr Evaluator::EvaluateQuery(std::unique_ptr<Query> &query) {
  Synonym selected_synonym = query->get_selected_synonyms().at(0);
  EntityId entity = query->get_synonym(selected_synonym);
  EntityPtrList all_entities = master_entity_factory_.GetAllFromPKB(
      entity, pkb_);
  QueryResultPtr result = std::make_unique<QueryResult>(all_entities);
//
//  for (std::unique_ptr<Clause> &clause : query->get_clauses()) {
//    // I'm not exactly sure of all the breakdown of different
//    // types of clauses yet, but this is my rough working
//    if (clause->IsExact()) {
//      // CLAUSE is type that returns only TRUE or FALSE
//      // TODO(JL): evaluateExactClause()
//      // if TRUE, continue, if FALSE, clear results
//      continue;
//    }
//
//    if (clause->HasWildcard()) {
//      // TODO(JL): evaluateWildcardClause()
//      continue;
//    }
//
//    // Has one synonym
//
//    // TODO(JL): if CLAUSE has no relation with the selected synonym
//    // then just continue
//
//    QueryResult clause_result = clause->Evaluate(std::move(pkb_));
//    result->IntersectWith(clause_result);
//  }

  return result;
}
}  // namespace qps
