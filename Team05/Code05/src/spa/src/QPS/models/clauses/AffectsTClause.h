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
};

}  // namespace qps
