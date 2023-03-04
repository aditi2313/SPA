#include <utility>
#include <unordered_set>

#include "Validator.h"
#include "QPS/factories/MasterClauseFactory.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;

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
    if (!master_clause_factory_.Validate(
        clause->get_rel_name(), clause->get_arg1(), clause->get_arg2())) {
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
}  // namespace qps
