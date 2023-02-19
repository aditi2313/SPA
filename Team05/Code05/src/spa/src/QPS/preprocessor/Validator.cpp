#include <utility>
#include "Validator.h"
#include "common/Exceptions.h"

namespace qps {

bool Validator::validate(std::unique_ptr<Query> &query) {

  if (IsWildcard(query) && SynonymCheck(query) && DesignEntitySynonyms(query) &&
      isDeclaredOnce(query)) {
    return true;
  }
  throw PqlSemanticErrorException("Semantic error");
}

// used to ensure that the design entity is correct
bool Validator::DesignEntitySynonyms(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    if (!clause->ValidateSynonymTypes()) {
      throw PqlSemanticErrorException("Wrong synonym type");
    }
  }
  return true;
}
// Uses: line(int), variables the line uses(vector)
// Follows : line(int), the line that this line follows / comes after(int)
// Parent : line(int), the line that is the parent of this line(int)
// Modifies : line(int), variables that are being modified in this line(vector)
// Assign : line(int), the variable that is being assigned to in that
// line(string), expression(unique pointer to ast::ExprNode)

// Returns false if the clauses have a wildcard
// declared as arg1 in the Modifies/Uses relationship
bool Validator::IsWildcard(QueryPtr &query) {
  // TODO(SP) edit it to check for clause type first.
  // As of now checks all clauses as all of them are modifies
  for (auto &clause : query->get_clauses()) {
    if (clause->isModifies_Uses()) {
      if (clause->get_arg1()->IsWildcard()) {
        throw PqlSemanticErrorException(
            "WildCard used as first arg in Uses or Modifies");
      }
    }
    return true;
  }
}
// Returns false if there is a clause
// used in the Query that has not been declared as a synonym previously.
bool Validator::SynonymCheck(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    if (clause->get_arg1()->IsIdent() || clause->get_arg2()->IsIdent()) {
      throw PqlSemanticErrorException("Synonym used has not been declared");
    }
    return true;
  }
}

bool Validator::isDeclaredOnce(QueryPtr &query) {
  std::unordered_set<std::string> syn_names;
  for (auto &syn : query->get_declared_synonyms()) {
    if (syn_names.count(syn->get_syn_id())) {
      throw PqlSemanticErrorException("Synonym declared more than once");
    }
    syn_names.insert(syn->get_syn_id());
  }
  return true;
}
}  // namespace qps
