#pragma once

#include <utility>

#include "ReversibleClause.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between lines
class AffectsClause : public ReversibleClause {
 public:
  AffectsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause(ClauseType::kAffects,
               std::move(arg1),
               std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto affected_lines = pkb->Affects(index.get_int());
    AddList(affected_lines, results);
  }

  inline void ReverseIndex(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto affecting_line = pkb->ReverseAffects(index.get_int());
    results.insert(Entity(affecting_line));
  }
};

}  // namespace qps
