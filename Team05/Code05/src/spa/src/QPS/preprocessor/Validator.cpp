#include <utility>
#include "Validator.h"

namespace qps {

bool Validator::validate(std::unique_ptr<Query> &query) {
  std::vector<std::unique_ptr<Clause>> &clauses = query->get_clauses();
  std::vector<SynonymPtr> synonyms = query->get_declared_synonyms();

  return IsWildcard(clauses);
}

// TODO(Sarthak) check for the type of synonym
// used to ensure that the design entity is correct
 bool Validator::DesignEntitySynonyms(
    std::vector<std::unique_ptr<Clause>> clauses,
    std::vector<SynonymPtr> synonyms) {
     for (auto & Clause : clauses) {
         if (typeid(*Clause).name() == "class ModifiesClause") {
             return true;
         }
         else if (typeid(*Clause).name() == "class UsesClause") {
             return true;
         }
         else if (typeid(*Clause).name() == "class FollowsClause") {
             return true;
         }
         else if (typeid(*Clause).name() == "class ParentClause") {
             return true;
         }
         else if (typeid(*Clause).name() == "class AssignClause") {
             return true;
         }
         else {
             return true;
         }


  return true;
 }
//Uses: line(int), variables the line uses(vector)
//Follows : line(int), the line that this line follows / comes after(int)
//Parent : line(int), the line that is the parent of this line(int)
//Modifies : line(int), variables that are being modified in this line(vector)
//Assign : line(int), the variable that is being assigned to in that line(string), expression(unique pointer to ast::ExprNode)

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
bool Validator::SynonymCheck(QueryPtr &query) {
  for (auto &clause : query->get_clauses()) {
    if (clause->get_arg1()->IsSynonym()) {
      auto arg = dynamic_cast<SynonymArg *>(clause->get_arg1().get());
      if (!query->is_declared_synonym_name(arg->get_syn_name())) {
        std::cout << "first arg is false";
        return false;
      }
    }

    if (clause->get_arg2()->IsSynonym()) {
      auto arg = dynamic_cast<SynonymArg *>(clause->get_arg2().get());
      if (!query->is_declared_synonym_name(arg->get_syn_name())) {
        std::cout << "second arg is false";
        return false;
      }
    }
  }
  return true;
}
}  // namespace qps
