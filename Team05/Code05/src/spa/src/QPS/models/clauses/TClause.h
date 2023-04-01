#pragma once

#include <utility>

#include "Clause.h"


namespace qps {

class TClause : public Clause {
 public:
  TClause(ClauseType clause_type, ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(clause_type, std::move(arg1), std::move(arg2)) {}
  inline void Filter(const EntitySet& lhs, const EntitySet& rhs,
                     Table::TwoSynonymRows& results_r,
                     const pkb::PKBReadPtr& pkb) override {
    if (rhs.size() != 1) {
      Clause::Filter(lhs, rhs, results_r, pkb);
      return;
    }
    const Entity& val = *rhs.begin();
    for (auto& index : lhs) {
      if (TIndex(index, pkb, val)) {
        results_r.emplace_back(index, val);
      }
    }
  }
  virtual bool TIndex(const Entity& index, const pkb::PKBReadPtr& pkb,
                      const Entity& reference) = 0;
};

}  // namespace qps
