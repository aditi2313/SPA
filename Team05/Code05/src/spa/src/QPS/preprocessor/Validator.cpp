#pragma once
#include "Validator.h"




namespace qps {


Query Validator::validator(Query query) { 
    std::vector<std::unique_ptr<Clause>> clauses = query.get_clauses();
    std::vector<std::string> synonyms =
        query.Query::get_selected_synonyms();


    if (isWildcard(clauses) || SynonymCheck(clauses, synonyms)) {
      return query;
    } else {
      throw PqlSemanticErrorException("Semantic error");
    }

}

//TODO(Sarthak) check for the type of synonym used to ensure that the design entity is correct
bool Validator::DesignEntitySynonyms(std::vector<std::unique_ptr<Clause>> clauses,
    std::vector<std::string> synonyms) {

}

// Returns false if the clauses have a wildcard declared as arg1 in the Modifies/Uses relationship

bool Validator::isWildcard(std::vector<std::unique_ptr<Clause>> clauses) {
    //TODO edit it to check for clause type first. As of know checks all clauses as all of them are modifies
    for (const auto &ptr : clauses) {
    auto clause = *ptr;
    std::string arg1 = clause.getarg1().to_string();
    if (arg1 == "_") {
        return false;
    }

    return true;
}

}
//Returns false if there is a clause used in the Query that has not been declared as a synonym previously.  
bool Validator::SynonymCheck(
        std::vector<std::unique_ptr<Clause>> clauses,
        std::vector<std::string> synonyms) {
  

  for (const auto &ptr : clauses) {
    auto clause = *ptr;
    std::string arg1 = clause.getarg1().to_string();
    std::string arg2 = clause.getarg2().to_string();

    if (!isdigit(arg1[0]) && !arg1._Starts_with("\"")) {
      if (std::find(synonyms.begin(), synonyms.end(), arg1) == synonyms.end()) {
        return false;
      }
    }
    if (!isdigit(arg2[0]) && !arg2._Starts_with("\"")) {
      if (std::find(synonyms.begin(), synonyms.end(), arg2) == synonyms.end()) {
        return false;
      }
    }

  }

  return true;
}
}  // namespace qps

