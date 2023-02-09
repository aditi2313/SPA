#include <utility>
#include "Validator.h"

namespace qps {

bool Validator::validate(std::unique_ptr<Query> &query) {
  std::vector<std::unique_ptr<Clause>> &clauses = query->get_clauses();
  std::vector<std::string> synonyms = query->get_selected_synonyms();

  return IsWildcard(clauses);
}

// TODO(Sarthak) check for the type of synonym
// used to ensure that the design entity is correct
bool Validator::DesignEntitySynonyms(
    std::vector<std::unique_ptr<Clause>> clauses,
    std::vector<std::string> synonyms) {
  return true;
}

// Returns false if the clauses have a wildcard
// declared as arg1 in the Modifies/Uses relationship
bool Validator::IsWildcard(std::vector<std::unique_ptr<Clause>> &clauses) {
  // TODO(SP) edit it to check for clause type first.
  // As of now checks all clauses as all of them are modifies
  for (auto &clause : clauses) {
    if (clause->get_arg1()->IsWildcard()) return false;
  }
  return true;
}
// Returns false if there is a clause
// used in the Query that has not been declared as a synonym previously.
bool Validator::SynonymCheck(std::vector<std::unique_ptr<Clause>> &clauses,
                             std::vector<std::string> synonyms) {
  for (auto &clause : clauses) {
//    std::string arg1 = clause->get_arg1().to_string();
//    std::string arg2 = clause->get_arg2().to_string();
//
//    std::cout << "args all work";
//    if (!isdigit(arg1[0]) && !arg1.rfind("\"", 0) == 0) {
//      if (std::find(synonyms.begin(), synonyms.end(), arg1)
//      == synonyms.end()) {
//        std::cout << "first arg is false";
//        return false;
//      }
//    }
//    if (!isdigit(arg2[0]) && !arg2.rfind("\"", 0) == 0) {
//      if (std::find(synonyms.begin(), synonyms.end(), arg2)
//      == synonyms.end()) {
//        std::cout << "second arg is false";
//        return false;
//      }
//    }
  }
  return true;
}
}  // namespace qps
