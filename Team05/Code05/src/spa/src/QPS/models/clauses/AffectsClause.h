#pragma once

#include <utility>

#include "Clause.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between lines
class AffectsClause : public Clause {
 public:
  AffectsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(ClauseType::kAffects,
               std::move(arg1),
               std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto affected_lines = pkb->Affects(index.get_int());
    for (auto &affected_line : affected_lines) {
      results.insert(Entity(affected_line));
    }
  }
};

}  // namespace qps
