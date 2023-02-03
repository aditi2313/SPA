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
  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }

  const inline void add_clause(std::unique_ptr<Clause> &&clause) {
    clauses_.push_back(std::move(clause));
  }

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

  bool operator==(const Query &other) const {
    return (
        clauses_ == other.clauses_
            && synonym_declarations_ == other.synonym_declarations_
            && selected_synonyms_ == other.selected_synonyms_
    );
  }

 private:
  std::vector<std::unique_ptr<Clause>> clauses_;
  std::unordered_map<std::string, models::EntityStub> synonym_declarations_;
  std::vector<std::string> selected_synonyms_;
};
}  // namespace qps

