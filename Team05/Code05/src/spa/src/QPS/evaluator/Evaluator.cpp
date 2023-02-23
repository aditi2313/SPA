#include "Evaluator.h"

#include <set>

namespace qps {
// Initialize every synonym in the query with all possible values.
void Evaluator::InitializeSynonyms(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  for (auto &syn : query->get_declared_synonyms()) {
    EntityPtrList list = master_entity_factory_->GetAllFromPKB(
        syn->get_entity_name(), pkb);
    syn->set_possible_entities(list);
  }
}

QueryResultPtr Evaluator::EvaluateQuery(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  InitializeSynonyms(query, pkb);

  for (int i = 0; i < 2; ++i) {
    for (auto &clause : query->get_clauses()) {
      bool clause_result = EvaluateClause(query, clause, pkb);

      if (!clause_result) {
        // Clause is false, can immediately return empty result.
        return std::make_unique<QueryResult>();
      }
    }
  }

  // For Basic SPA, just one for now.
  SynonymName selected_synonym = query->get_selected_synonyms().at(0);
  QueryResultPtr result = std::make_unique<QueryResult>(
      query->get_synonym(selected_synonym)->get_possible_entities());
  return result;
}

// Returns true if there are still results, false otherwise
bool Evaluator::EvaluateClause(
    QueryPtr &query, ClausePtr &clause, std::unique_ptr<pkb::PKBRead> &pkb) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  // Fill with candidate values
  EntityPtrList LHS;
  EntityPtrList RHS;

  InitializeEntitiesFromArgument(query, arg1, pkb, clause->LHS(), LHS);
  InitializeEntitiesFromArgument(query, arg2, pkb, clause->RHS(), RHS);

  bool is_symmetric = arg1->IsSynonym() && (*arg1 == *arg2);

  // Takes care of duplicates
  EntityPtrHashset RHS_results(0, EntityPtrHash, EntityPtrEqual);
  EntityPtrHashset LHS_results(0, EntityPtrHash, EntityPtrEqual);

  // Query PKB with LHS possible values
  for (auto &index : LHS) {
    EntityPtrList results;
    if (arg2->IsWildcard()) {
      // Just index and return all
      results = clause->Index(index, master_entity_factory_, pkb);
    } else {
      // Is synonym or exact (int or ident), need filter
      results = is_symmetric
                ? clause->SymmetricFilter(index, master_entity_factory_, pkb)
                : clause->Filter(index, RHS, master_entity_factory_, pkb);
    }

    for (auto &entity : results) {
      // Remove duplicates
      RHS_results.insert(std::move(entity));
    }

    if (!results.empty()) {
      LHS_results.insert(index->Copy());
    }
  }

  // Update list of possible values for arg1 and/or arg2
  // if they are synonyms
  UpdateSynonymEntityList(query, arg1, LHS_results);
  UpdateSynonymEntityList(query, arg2, RHS_results);

  return !RHS_results.empty();
}

void Evaluator::InitializeEntitiesFromArgument(
    QueryPtr &query, ArgumentPtr &arg, std::unique_ptr<pkb::PKBRead> &pkb,
    EntityName entity_name, EntityPtrList &result) {
  if (arg->IsExpression()) return;
  if (arg->IsWildcard()) {
    for (auto &entity :
        master_entity_factory_->GetAllFromPKB(entity_name, pkb)) {
      result.push_back(std::move(entity));
    }
    return;
  }
  if (arg->IsSynonym()) {
    SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
    SynonymPtr &synonym = query->get_synonym(synonym_arg->get_syn_name());
    for (auto &entity : synonym->get_possible_entities()) {
      result.push_back(entity->Copy());
    }
    return;
  }

  // Int or Ident Arg
  if (arg->IsStmtRef()) {
    // INT
    IntegerArg *integer_arg = dynamic_cast<IntegerArg *>(arg.get());
    result.push_back(master_entity_factory_->CreateInstance(
        entity_name,
        integer_arg->get_number()));
  }

  if (arg->IsEntRef()) {
    // IDENT
    IdentArg *ident_arg = dynamic_cast<IdentArg *>(arg.get());
    result.push_back(master_entity_factory_->CreateInstance(
        entity_name,
        ident_arg->get_ident()));
  }
}

void Evaluator::UpdateSynonymEntityList(
    QueryPtr &query, ArgumentPtr &arg,
    EntityPtrHashset const &result) {
  if (!arg->IsSynonym()) return;  // Not a synonym

  SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
  SynonymPtr &synonym = query->get_synonym(synonym_arg->get_syn_name());

  EntityPtrList new_entity_ptr_list;
  for (auto &entity : result) {
    new_entity_ptr_list.push_back(entity->Copy());
  }

  synonym->set_possible_entities(new_entity_ptr_list);
}
}  // namespace qps
