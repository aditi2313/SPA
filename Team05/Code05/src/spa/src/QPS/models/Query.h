#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Clause.h"
#include "models/Entity.h"
#include "Synonym.h"
#include "PQL.h"

using models::SynonymName;

namespace qps {
class Query {
 public:
  // Set a synonym declaration
  inline void declare_synonym(SynonymName syn_id, models::EntityName entity_id) {
    synonym_declarations_.push_back(std::make_unique<Synonym>(syn_id, entity_id));
  }

  // Returns true if `token` is a synonym that has been declared
  inline bool is_declared_synonym_id(std::string token) {
    for(auto &syn : synonym_declarations_) {
      if(syn->get_syn_id() == token) return true;
    }
    return false;
  }

  // Returns true if `syn` has been declared
  inline bool does_synonym_exist(Synonym syn) {
    for(auto &declared_syn : synonym_declarations_) {
      if(syn == *declared_syn) return true;
    }
    return false;
  }

  inline EntityName get_declared_synonym(std::string token) {
    for(auto &syn : synonym_declarations_) {
      if(syn->get_syn_id() == token) return syn->get_entity_id();
    }
    throw std::runtime_error("Synonym has not been declared");
  }

  // A selected synonym is a synonym that comes after `Select`
  // (Note: to support Advanced SPA requirements, currently
  // it will always be just one selected synonym)
  inline void add_selected_synonym(std::string synonym) {
    selected_synonyms_.push_back(synonym);
  }

  // A selected synonym is a synonym that comes after `Select`
  inline std::vector<std::string> get_selected_synonyms() {
    return selected_synonyms_;
  }

  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }

  inline void add_clause(std::unique_ptr<Clause> &&clause) {
    clauses_.push_back(std::move(clause));
  }

  inline bool operator==(const Query &other) const {
    if (clauses_.size() != other.clauses_.size()) return false;
    int num_clauses = clauses_.size();
    for (int i = 0; i < num_clauses; ++i) {
      if (*clauses_.at(i) != *other.clauses_.at(i)) return false;
    }

    if(synonym_declarations_.size() != other.synonym_declarations_.size()) return false;


    return (synonym_declarations_ == other.synonym_declarations_ &&
        selected_synonyms_ == other.selected_synonyms_);
  }

  inline ArgumentPtr CreateArgument(std::string token) {
    if (is_declared_synonym_id(token)) {
      return std::make_unique<SynonymArg>(token);
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
  std::vector<SynonymPtr> synonym_declarations_;
  std::vector<SynonymName> selected_synonyms_;
  std::vector<std::unique_ptr<Clause>> clauses_;
};

using QueryPtr = std::unique_ptr<Query>;
}  // namespace qps
