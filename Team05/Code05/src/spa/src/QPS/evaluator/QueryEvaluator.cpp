#include "QueryEvaluator.h"
#include "QPS/models/Table.h"
#include "TableJoiner.h"
#include "ClauseEvaluator.h"

namespace qps {
QueryResultPtr QueryEvaluator::EvaluateQuery(QueryPtr &query) {
  ClauseEvaluator clause_evaluator(pkb_);

  if (!query->is_boolean_query()) {
    // TODO(JL): Extend to support multiple synonyms
    SynonymName selected_synonym = query->get_selected_synonyms().at(0);
    EntityName entity_name = query->get_declared_synonym_entity_name(
        selected_synonym);
    EntitySet initial_entities = master_entity_factory_->GetAllFromPKB(
        entity_name);

    table_ = Table(selected_synonym, initial_entities);
  }

  for (auto &clause : query->get_clauses()) {
    Table clause_table;
    EntitySet LHS, RHS;

    InitializeEntitiesFromArgument(clause->get_arg1(), clause->LHS(), LHS);
    InitializeEntitiesFromArgument(clause->get_arg2(), clause->RHS(), RHS);

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

  EntitySet results = table_.Select(
      query->get_selected_synonyms().at(0));
  QueryResultPtr result = std::make_unique<ListQueryResult>(
      results);

  return result;
}

// Given an argument, initialize into `result`
// all the possible values for that argument
void QueryEvaluator::InitializeEntitiesFromArgument(
    ArgumentPtr &arg,
    EntityName entity_name,
    EntitySet &result) {
  if (arg->IsExpression()) return;

  if (arg->IsSynonym()) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    if (table_.HasColumn(syn_arg->get_syn_name())) {
      result = table_.Select(syn_arg->get_syn_name());
    } else {
      result = master_entity_factory_->GetAllFromPKB(
          syn_arg->get_entity_name());
    }
    return;
  }

  if (arg->IsWildcard()) {
    for (auto &entity :
        master_entity_factory_->GetAllFromPKB(entity_name)) {
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
