#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Clause.h"
#include "models/Entity.h"
#include "PQL.h"

using models::Synonym;

namespace qps {
class Query {
 public:
  // Returns false if synonym already exists in the declaration hashmap.
  inline bool set_synonym(Synonym synonym, models::EntityId entity) {
    if (synonym_declarations_.find(synonym) != synonym_declarations_.end())
      return false;
    synonym_declarations_[synonym] = entity;
    return true;
  }

  inline models::EntityId get_synonym(Synonym synonym) {
    return synonym_declarations_.at(synonym);
  }

  inline bool is_synonym(std::string token) {
    return synonym_declarations_.find(token) != synonym_declarations_.end();
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

  inline void add_clause(std::unique_ptr<Clause> &&clause) {
    clauses_.push_back(std::move(clause));
  }
  // TODO(jl): Technically a query with the same clauses
  // but different order should compare as equal but I will
  // leave that logic as a TODO in the future
  inline bool operator==(const Query &other) const {
    if (clauses_.size() != other.clauses_.size()) return false;
    int num_clauses = clauses_.size();
    for (int i = 0; i < num_clauses; ++i) {
      if (*clauses_.at(i) != *other.clauses_.at(i)) return false;
    }
    return (synonym_declarations_ == other.synonym_declarations_ &&
        selected_synonyms_ == other.selected_synonyms_);
  }

  inline ArgumentPtr CreateArgument(std::string token) {
    if (is_synonym(token)) {
      return std::make_unique<SynonymArg>(token, get_synonym(token));
    }
    if (token == "_") {
      return std::make_unique<Wildcard>();
    }

    if (PQL::is_ident(token)) {
      return std::make_unique<IdentArg>(token);
    }

    if (PQL::is_integer(token)) {
      return std::make_unique<IntegerArg>(stoi(token));
    }

    return std::make_unique<ExpressionArg>(token);
  }

 private:
  std::unordered_map<Synonym, models::EntityId> synonym_declarations_;
  std::vector<Synonym> selected_synonyms_;
  std::vector<std::unique_ptr<Clause>> clauses_;
};

using QueryPtr = std::unique_ptr<Query>;
}  // namespace qps
