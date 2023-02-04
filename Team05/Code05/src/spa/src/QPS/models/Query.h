#pragma once

#include <vector>
#include <memory>
#include "Clause.h"
#include <unordered_map>
#include <QPS/models/Clause.h>

namespace qps {
class Query {
 public:
  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }
  //Temporary use of method from JL will move after merge
  inline models::EntityStub get_synonym(std::string synonym) {
    return synonym_declarations_.at(synonym);
  }
  inline std::vector<std::string> get_selected_synonyms() {
    return selected_synonyms_;
  }
 private:
  std::vector<std::unique_ptr<Clause>> clauses_;
  std::unordered_map<std::string, models::EntityStub> synonym_declarations_;
  std::vector<std::string> selected_synonyms_;
};
}  // namespace qps

