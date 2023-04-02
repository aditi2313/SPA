#pragma once

#include <utility>

#include "Clause.h"

namespace qps {
class ReversibleClause : public Clause {
 public:
  ReversibleClause(ClauseType clause_type, ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(clause_type, std::move(arg1), std::move(arg2)) {}

  inline virtual void ReverseIndex(const Entity& index,
                                   const pkb::PKBReadPtr& pkb,
                                   EntitySet& results) = 0;
  inline void Filter(const EntitySet& lhs, const EntitySet& rhs,
                     Table::TwoSynonymRows& results_r,
                     const pkb::PKBReadPtr& pkb) override {
    bool reverse = lhs.size() > rhs.size();
    auto& curr_indexes = reverse ? rhs : lhs;
    auto& filter_indexes = reverse ? lhs : rhs;
    for (auto& index : curr_indexes) {
      EntitySet results;
      reverse ? ReverseIndex(index, pkb, results) : Index(index, pkb, results);
      for (auto& entity : results) {
        if (!filter_indexes.count(entity)) continue;
        reverse ? results_r.emplace_back(entity, index)
                : results_r.emplace_back(index, entity);
      }
    }
  }

  inline void WildcardFilterForRHS(
      const EntitySet &LHS,
      const EntitySet& RHS,
      const pkb::PKBReadPtr &pkb,
      EntitySet& RHS_results) override {
    EntitySet results;
    for(auto &index : RHS) {
      ReverseIndex(index, pkb, results);
      if (!results.empty()) {
        RHS_results.insert(index);
      }
    }
  }

  template <class Reader>
  void WriteSecondIndexesFromReader(Reader& reader, EntitySet& results) {
    while (!reader.reached_end()) {
      auto& data = reader.read_data();
      auto copied = data.get_index();
      results.insert(Entity(copied));
      reader.increment();
    }
  }
};

}  // namespace qps
