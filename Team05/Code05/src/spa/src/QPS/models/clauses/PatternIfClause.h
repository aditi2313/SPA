#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ConditionIndexFilter;

namespace qps {
// RS between a statement and a list of (control) variables
class PatternIfClause : public Clause {
 public:
  PatternIfClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kPatternIf, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::ConditionData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<ConditionIndexFilter>(key);
          return std::move(pkb->Condition(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::ConditionData data) {
          for (auto child : data.get_variables()) {
            result.insert(Entity(child));
          }
        },
        results);
  }
};

}  // namespace qps
