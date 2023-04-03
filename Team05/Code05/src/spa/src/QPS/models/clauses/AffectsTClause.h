#pragma once

#include <utility>

#include "Clause.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between lines
class AffectsTClause : public Clause {
 public:
  AffectsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(ClauseType::kAffectsT,
               std::move(arg1),
               std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto affectsT_lines = pkb->AffectsT(index.get_int());
    AddList(affectsT_lines, results);
  }

  inline bool WildcardIndex(const Entity &index,
                            const pkb::PKBReadPtr &pkb) override {
    // Optimisation: check if Affects return anything
    EntitySet results;
    Index(index, pkb, results);
    return results.empty();
  }
};

}  // namespace qps
