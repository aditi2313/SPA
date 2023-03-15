#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

namespace qps {
// RS between a statement and a list of variables
class PatternIfClause : public Clause {
 public:
  PatternIfClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kPatternIf, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    // TODO(JL)
  }
};

}  // namespace qps
