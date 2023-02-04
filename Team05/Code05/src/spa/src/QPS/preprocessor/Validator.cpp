#include "Validator.h"

#include "Validator.h"
#include <memory>
#include <unordered_map>
#include <models/EntityStub.h>
#include <QPS/models/Query.h>


namespace qps {


    Query Validator::validator(Query query) { 
        std::vector<std::unique_ptr<Clause>> clauses = query.get_clauses();
        std::unordered_map<std::string, models::EntityStub> synonyms =
          query.get_selected_synonyms();

    }


    bool wildcard(std::vector<std::unique_ptr<Clause>> clauses) {
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

bool SynonymCheck(
        std::vector<std::unique_ptr<Clause>> clauses,
        std::unordered_map<std::string, models::EntityStub> synonyms) {
  

  for (const auto &ptr : clauses) {
    auto clause = *ptr;
    std::string arg1 = clause.getarg1().to_string();
    std::string arg2 = clause.getarg2().to_string();

    if (!isdigit(arg1[0]) && !arg1._Starts_with("\"")) {
      std::unordered_map<std::string, models::EntityStub>::const_iterator
          used1 = synonyms.find(arg1);
      if (used1 == synonyms.end()) {
        return false;
      }
    }
    if (!isdigit(arg2[0]) && !arg2._Starts_with("\"")) {
      std::unordered_map<std::string, models::EntityStub>::const_iterator
          used2 = synonyms.find(arg2);
      if (used2 == synonyms.end()) {
        return false;
      }
    }

  }

  return true;
}
}  // namespace qps

