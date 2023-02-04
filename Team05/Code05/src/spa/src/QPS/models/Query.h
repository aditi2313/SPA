#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <unordered_map>

#include "Clause.h"
#include "models/EntityStub.h"

namespace qps {
class Query {
 public:
  // Returns false if synonym already exists in the declaration hashmap.
  inline bool set_synonym(std::string synonym, models::EntityStub entity) {
    if (synonym_declarations_.find(synonym) != synonym_declarations_.end())
      return false;
    synonym_declarations_[synonym] = entity;
    return true;
  }

  inline models::EntityStub get_synonym(std::string synonym) {
    return synonym_declarations_.at(synonym);
  }

  inline void add_selected_synonym(std::string synonym) {
    selected_synonyms_.push_back(synonym);
  }

  inline std::vector<std::string> get_selected_synonyms() {
    return selected_synonyms_;
  }

  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }
 private:
  std::unordered_map<std::string, models::EntityStub> synonym_declarations_;
  std::vector<std::string> selected_synonyms_;
  std::vector<std::unique_ptr<Clause>> clauses_;
  std::unordered_map<std::string, models::EntityStub> synonym_declarations_;
  std::vector<std::string> selected_synonyms_;
};
}  // namespace qps

