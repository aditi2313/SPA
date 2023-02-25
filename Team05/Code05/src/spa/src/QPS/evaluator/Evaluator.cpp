#include "Evaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"

namespace qps {
// Initialize every synonym in the query with all possible values.
void Evaluator::InitializeSynonyms(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  for (auto &syn : query->get_declared_synonyms()) {
    EntitySet list = master_entity_factory_->GetAllFromPKB(
        syn->get_entity_name(), pkb);
    syn->set_possible_entities(list);
  }
}

QueryResultPtr Evaluator::EvaluateQuery(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  InitializeSynonyms(query, pkb);

  Table table;

  for (auto &clause : query->get_clauses()) {
    Table clause_table = EvaluateClause(query, clause, pkb);

    if (clause_table.Empty()) {
      // Clause is false, can immediately return empty result.
      return std::make_unique<QueryResult>();
    }

    table = TableJoiner::Join(table, clause_table);
  }

  SynonymName selected_synonym = query->get_selected_synonyms().at(0);

  if (table.Empty()) {
    // TODO(JL): Fix LOD Violation
    table = Table(selected_synonym,
                  query->get_synonym(selected_synonym)->get_possible_entities());
  }

  EntitySet results = table.Select(selected_synonym);
  QueryResultPtr result = std::make_unique<QueryResult>(
      results);

  return result;
}

// Returns true if there are still results, false otherwise
Table Evaluator::EvaluateClause(
    QueryPtr &query, ClausePtr &clause, std::unique_ptr<pkb::PKBRead> &pkb) {
  ArgumentPtr &arg1 = clause->get_arg1();
  ArgumentPtr &arg2 = clause->get_arg2();

  // Fill with candidate values
  EntitySet LHS;
  EntitySet RHS;

  InitializeEntitiesFromArgument(query, arg1, pkb, clause->LHS(), LHS);
  InitializeEntitiesFromArgument(query, arg2, pkb, clause->RHS(), RHS);

  bool is_symmetric = arg1->IsSynonym() && (*arg1 == *arg2);

  // Takes care of duplicates
  EntitySet RHS_results;
  EntitySet LHS_results;

  // Query PKB with LHS possible values
  for (auto &index : LHS) {
    EntitySet results;
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
      LHS_results.insert(index);
    }
  }

  // Update list of possible values for arg1 and/or arg2
  // if they are synonyms
  UpdateSynonymEntityList(query, arg1, LHS_results);
  UpdateSynonymEntityList(query, arg2, RHS_results);

  return Table();
}

void Evaluator::InitializeEntitiesFromArgument(
    QueryPtr &query, ArgumentPtr &arg, std::unique_ptr<pkb::PKBRead> &pkb,
    EntityName entity_name, EntitySet &result) {
  if (arg->IsExpression()) return;
  if (arg->IsWildcard()) {
    for (auto &entity :
        master_entity_factory_->GetAllFromPKB(entity_name, pkb)) {
      result.insert(std::move(entity));
    }
    return;
  }
  if (arg->IsSynonym()) {
    SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
    SynonymPtr &synonym = query->get_synonym(synonym_arg->get_syn_name());
    for (auto &entity : synonym->get_possible_entities()) {
      result.insert(entity);
    }
    return;
  }

  // Int or Ident Arg
  if (arg->IsStmtRef()) {
    // INT
    IntegerArg *integer_arg = dynamic_cast<IntegerArg *>(arg.get());
    result.insert(Entity(integer_arg->get_number()));
  }

  if (arg->IsEntRef()) {
    // IDENT
    IdentArg *ident_arg = dynamic_cast<IdentArg *>(arg.get());
    result.insert(Entity(ident_arg->get_ident()));
  }
}

void Evaluator::UpdateSynonymEntityList(
    QueryPtr &query, ArgumentPtr &arg,
    EntitySet const &result) {
  if (!arg->IsSynonym()) return;  // Not a synonym

  SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
  SynonymPtr &synonym = query->get_synonym(synonym_arg->get_syn_name());

  EntitySet new_entity_ptr_list;
  for (auto &entity : result) {
    new_entity_ptr_list.insert(entity);
  }

  synonym->set_possible_entities(new_entity_ptr_list);
}
}  // namespace qps
