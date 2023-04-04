#pragma once

#include <utility>

#include "Clause.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between lines
class AffectsTClause : public ReversibleClause {
 public:
  AffectsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause(ClauseType::kAffectsT,
               std::move(arg1),
               std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    pkb->CacheAllAffects();
    auto affectsT_lines = pkb->AffectsT(index.get_int());
    AddList(affectsT_lines, results);
  }

  inline void ReverseIndex(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    pkb->CacheAllAffects();
    auto affectingT_lines = pkb->ReverseAffectsT(index.get_int());
    AddList(affectingT_lines, results);
  }

  inline bool WildcardIndex(const Entity &index,
                            const pkb::PKBReadPtr &pkb) override {
    // Optimisation: just check if Affects return anything
    EntitySet results;
    auto affected_lines = pkb->Affects(index.get_int());
    return affected_lines.empty();
  }

  inline bool ReverseWildcardIndex(const Entity &index,
                                   const pkb::PKBReadPtr &pkb) override {
    // Optimisation: just check if ReverseAffects return anything
    EntitySet results;
    auto affected_lines = pkb->ReverseAffects(index.get_int());
    return affected_lines.empty();
  }
};

}  // namespace qps
