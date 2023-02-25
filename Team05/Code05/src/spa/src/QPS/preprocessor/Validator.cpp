#include <utility>
#include <unordered_set>
#include "Validator.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {

void Validator::Validate(std::unique_ptr<Query> &query) {
  ValidateSynonymsDeclaredExactlyOnce(query);
  ValidateSynonymsUsedAreDeclared(query);
  ValidateClauseArguments(query);
}

// Used to ensure that the design entity for synonyms is correct
// as per clause: e.g Follows(arg1, arg2)
// if arg1 is a synonym it should be a statement or a
// sub-type of statement (read, print, call...)
// ValidateArguments also check if the first argument for
// Modifies and Uses is a wildcard, which is not allowed
void Validator::ValidateClauseArguments(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    ValidateArgumentSynonymType(
        clause->get_arg1(), clause->LHS(), clause->IsExactType());
    ValidateArgumentSynonymType(
        clause->get_arg2(), clause->RHS(), clause->IsExactType());
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

  for (auto &clause : query->get_clauses()) {
    ValidateArgumentSynonymDeclared(query, clause->get_arg1());
    ValidateArgumentSynonymDeclared(query, clause->get_arg2());
    if (!clause->IsWildcardAllowedAsFirstArg()
        && clause->get_arg1()->IsWildcard()) {
      throw PqlSemanticErrorException(
          "Wildcard is not allowed as first argument "
          "for Modifies and Uses clauses");
    }
  }
}

// If argument is a synonym, check if it has been declared
void Validator::ValidateArgumentSynonymDeclared(
    QueryPtr &query, ArgumentPtr &arg) {
  if (!arg->IsSynonym()) return;
  SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
  if (!query->is_synonym_name_declared(synonym_arg->get_syn_name())) {
    throw PqlSemanticErrorException("Undeclared synonym argument in clause");
  }
}

// If argument is a synonym, check that it is of the correct type
void Validator::ValidateArgumentSynonymType(ArgumentPtr &arg,
                                            EntityName expected_entity_name,
                                            bool is_exact_match) {
  if (!arg->IsSynonym()) return;
  SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg.get());
  EntityName actual_entity_name = is_exact_match
                                  ? synonym_arg->get_entity_name()
                                  : synonym_arg->get_base_entity_name();
  if (actual_entity_name != expected_entity_name) {
    throw PqlSemanticErrorException("Incompatible synonym type in clause");
  }
}
}  // namespace qps
