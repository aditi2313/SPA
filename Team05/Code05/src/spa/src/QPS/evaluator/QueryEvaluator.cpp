#include "QueryEvaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"

namespace qps {
// Initialize every synonym in the query with all possible values.
void QueryEvaluator::InitializeSynonyms(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  for (auto &syn : query->get_declared_synonyms()) {
    EntitySet list = master_entity_factory_->GetAllFromPKB(
        syn->get_entity_name(), pkb);
    syn->set_possible_entities(list);
  }
}

QueryResultPtr QueryEvaluator::EvaluateQuery(
    QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb) {
  InitializeSynonyms(query, pkb);

  SynonymName selected_synonym = query->get_selected_synonyms().at(0);
  Table table = Table(selected_synonym,
                      query->get_declared_synonym_entities(selected_synonym));

  for (auto &clause : query->get_clauses()) {
    Table clause_table;
    EvaluateClause(query, clause, clause_table, pkb);

    if (clause_table.Empty()) {
      // Clause is false, can immediately return empty result.
      return std::make_unique<QueryResult>();
    }

    table = TableJoiner::Join(table, clause_table);
  }

  EntitySet results = table.Select(selected_synonym);
  QueryResultPtr result = std::make_unique<QueryResult>(
      results);

  return result;
}

void QueryEvaluator::InitializeEntitiesFromArgument(
    QueryPtr &query, ArgumentPtr &arg, std::unique_ptr<pkb::PKBRead> &pkb,
    EntityName entity_name, EntitySet &result) {
  if (arg->IsExpression()) return;
  if (arg->IsWildcard()) {
    for (auto &entity :
        master_entity_factory_->GetAllFromPKB(entity_name, pkb)) {
      result.insert(entity);
    }
    return;
  }
  if (arg->IsSynonym()) {
    SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
    auto entities = query->get_declared_synonym_entities(synonym_arg->get_syn_name());
    for (auto &entity : entities) {
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
}  // namespace qps
