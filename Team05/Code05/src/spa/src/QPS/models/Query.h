#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Clause.h"
#include "common/Utiity.h"
#include "Entity.h"
#include "Synonym.h"
#include "PQL.h"

using models::SynonymName;

namespace qps {
class Query {
 public:
  // Set a synonym declaration
  inline void declare_synonym(
      SynonymName syn_id, models::EntityName entity_name) {
    synonym_declarations_.push_back(
        std::make_unique<Synonym>(syn_id, entity_name));
  }

  // Returns true if `token` is a synonym that has been declared
  inline bool is_declared_synonym_name(std::string token) {
    for (auto &syn : synonym_declarations_) {
      if (syn->get_syn_name() == token) return true;
    }
    return false;
  }

  // Returns true if `syn` has been declared
  inline bool does_synonym_exist(Synonym syn) {
    for (auto &declared_syn : synonym_declarations_) {
      if (syn == *declared_syn) return true;
    }
    return false;
  }

  inline SynonymPtr &get_synonym(std::string token) {
    for (auto &syn : synonym_declarations_) {
      if (syn->get_syn_name() == token) return syn;
    }
    throw std::runtime_error("Synonym has not been declared");
  }

  inline std::vector<SynonymPtr> &get_declared_synonyms() {
    return synonym_declarations_;
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
    if (!util::CompareVectorOfPointers(clauses_, other.clauses_)) return false;
    if (!util::CompareVectorOfPointers(
        synonym_declarations_, other.synonym_declarations_))
      return false;

    return selected_synonyms_ == other.selected_synonyms_;
  }

  ArgumentPtr CreateArgument(std::string token);

 private:
  std::vector<SynonymPtr> synonym_declarations_;
  std::vector<SynonymName> selected_synonyms_;
  std::vector<ClausePtr> clauses_;
};

using QueryPtr = std::unique_ptr<Query>;
}  // namespace qps
