#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ConditionIndexFilter;

namespace qps {
// RS between a statement and a list of (control) variables
class PatternWhileClause : public Clause {
 public:
  PatternWhileClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kPatternWhile, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::ConditionData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<ConditionIndexFilter>(key);
          return std::move(pkb->Condition(std::move(filter)));
        },
        [&](EntitySet &result, pkb::ConditionData data) {
          AddList(data.get_variables(), result);
        },
        results);
  }
};

}  // namespace qps
