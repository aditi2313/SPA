#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "QPS/models/clauses/Clause.h"
#include "common/Utility.h"
#include "Entity.h"
#include "Synonym.h"
#include "PQL.h"

namespace qps {
class Query {
 public:
  // Set a synonym declaration
  inline void declare_synonym(
      SynonymName syn_id, EntityType entity_type) {
    synonym_declarations_.push_back(
        std::make_unique<Synonym>(syn_id, entity_type));
  }

  // Returns true if `token` is a synonym that has been declared
  inline bool is_synonym_name_declared(std::string token) {
    for (auto &syn : synonym_declarations_) {
      if (syn->get_syn_name() == token) return true;
    }
    return false;
  }

  inline EntityType get_declared_synonym_entity_name(SynonymName syn_name) {
    for (auto &syn : synonym_declarations_) {
      if (syn->get_syn_name() == syn_name)
        return syn->get_entity_name();
    }
    throw std::runtime_error("Synonym has not been declared");
  }

  inline std::vector<SynonymPtr> &get_declared_synonyms() {
    return synonym_declarations_;
  }

  // A selected elem is an elem that comes after `Select`
  // Elem: Synonym | AttrRef
  inline void add_selected_elem(Elem elem) {
    selected_elems_.push_back(elem);
  }

  // A selected elem is an elem that comes after `Select`
  // Elem: Synonym | AttrRef
  inline std::vector<std::string> get_selected_elems() {
    return selected_elems_;
  }

  // Iterate through selected elems
  // If elem is a Synonym, just add elem
  // Else elem is an attrRef, and we split attrRef to
  // add the synonym portion
  inline std::vector<std::string> get_selected_synonyms() {
    std::vector<std::string> synonyms;
    for (auto &elem : selected_elems_) {
      if (PQL::is_attr_ref(elem)) {
        synonyms.push_back(PQL::split_attr_ref(elem).first);
      } else {
        synonyms.push_back(elem);
      }
    }
    return synonyms;
  }

  inline void set_boolean_query_to_true() {
    is_boolean_query_ = true;
  }

  inline bool is_boolean_query() {
    return is_boolean_query_;
  }

  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }

  inline void add_clause(std::unique_ptr<Clause> &clause) {
    clauses_.push_back(std::move(clause));
  }

  inline void add_clause(std::unique_ptr<Clause> &&clause) {
    clauses_.push_back(std::move(clause));
  }

  inline bool operator==(const Query &other) const {
    if (!util::CompareVectorOfPointers(clauses_, other.clauses_)) return false;
    if (!util::CompareVectorOfPointers(
        synonym_declarations_, other.synonym_declarations_))
      return false;

    return selected_elems_ == other.selected_elems_;
  }

 private:
  bool is_boolean_query_ = false;
  std::vector<SynonymPtr> synonym_declarations_;
  // Elem = Synonym | AttrRef
  std::vector<Elem> selected_elems_;
  std::vector<ClausePtr> clauses_;
};

using QueryPtr = std::unique_ptr<Query>;
}  // namespace qps
