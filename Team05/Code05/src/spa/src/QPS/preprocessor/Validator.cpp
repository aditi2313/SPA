#include <utility>
#include <unordered_set>

#include "Validator.h"
#include "QPS/factories/MasterClauseFactory.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;

void Validator::Validate(std::unique_ptr<Query> &query) {
  InitializeSynonymEntityTypes(query);

  ValidateSynonymsDeclaredExactlyOnce(query);
  ValidateSynonymsUsedAreDeclared(query);
  ValidateClauseArguments(query);
  ValidateAttrRefs(query);
}

void Validator::InitializeSynonymEntityTypes(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    InitializeSynonymEntityTypes(query, clause->get_arg1());
    InitializeSynonymEntityTypes(query, clause->get_arg2());
  }
}

void Validator::InitializeSynonymEntityTypes(
    QueryPtr &query, ArgumentPtr &arg) {
  if (!arg->IsSynonym()) return;
  SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
  SynonymName syn_name = syn_arg->get_syn_name();
  if (!query->is_synonym_name_declared(syn_name))
    throw PqlSemanticErrorException("Undeclared synonym in clause");

  EntityType entity_type = query->get_declared_synonym_entity_type(syn_name);
  syn_arg->set_entity_type(entity_type);
}

// Used to ensure that the design entity for synonyms is correct
// as per clause: e.g Follows(arg1, arg2)
// if arg1 is a synonym it should be a statement or a
// sub-type of statement (read, print, call...)
// ValidateArguments also check if the first argument for
// Modifies and Uses is a wildcard, which is not allowed
void Validator::ValidateClauseArguments(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    if (!master_clause_factory_.Validate(
        clause->get_clause_type(), clause->get_arg1(), clause->get_arg2())) {
      throw PqlSemanticErrorException(
          "Mismatched entity types between argument and clause");
    }
  }
}

// Checks if all synonym names are declared only once.
// e.g variable v; while v; will throw error
void Validator::ValidateSynonymsDeclaredExactlyOnce(QueryPtr &query) {
  std::unordered_set<std::string> syn_names;
  for (auto &syn : query->get_declared_synonyms()) {
    if (syn_names.count(syn->get_syn_name())) {
      throw PqlSemanticErrorException("Synonym declared more than once");
    }
    syn_names.insert(syn->get_syn_name());
  }
}

// Checks if all synonym names used are declared.
void Validator::ValidateSynonymsUsedAreDeclared(QueryPtr &query) {
  for (auto syn_name : query->get_selected_synonyms()) {
    if (!query->is_synonym_name_declared(syn_name)) {
      throw PqlSemanticErrorException("Tried to Select an undeclared synonym");
    }
  }
}

// Checks if selected attrRefs are semantically correct.
// E.g s.stmt# and c.value are OK but s.varName and c.procName are not.
// Note that this check for `with` clauses arguments is also performed
// in ValidateClauseArguments
void Validator::ValidateAttrRefs(QueryPtr &query) {
  for (auto elem : query->get_selected_elems()) {
    if (PQL::is_attr_ref(elem)) {
      auto [syn_name, attr_name] = PQL::split_attr_ref(elem);
      auto entity_type = query->get_declared_synonym_entity_type(syn_name);
      if (!PQL::ValidateAttrRef(
          PQL::get_attr_type(attr_name), entity_type)) {
        throw PqlSemanticErrorException(
            "Selected attrRef has mismatched types");
      }
    }
  }
}
}  // namespace qps
