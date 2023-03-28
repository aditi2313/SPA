#pragma once

#include "Clause.h"

namespace qps {
class ReversableClause : public Clause {
 public:
  ReversableClause(ClauseType clause_type, ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(clause_type, std::move(arg1), std::move(arg2)) {}

  inline virtual void ReverseIndex(const Entity& index,
                                   const pkb::PKBReadPtr& pkb,
                                   EntitySet& result) = 0;
  inline virtual void Filter(const EntitySet& lhs, const EntitySet& rhs,
                             Table::TwoSynonymRows& results_r,
                             const pkb::PKBReadPtr& pkb) override {
    bool reverse = lhs.size() > rhs.size();
    auto& curr_indexes = reverse ? rhs : lhs;
    for (auto& index : curr_indexes) {
      EntitySet results;
      reverse ? ReverseIndex(index, pkb, results) : Index(index, pkb, results);
      if (results.empty()) continue;
      for (auto& entity : results) {
        if (!rhs.count(entity)) continue;
        results_r.emplace_back(index, entity);
      }
    }
  }
};

}  // namespace qps
