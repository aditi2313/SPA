#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::UsesIndexFilter;

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
    Clause::Index<pkb::UsesData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<UsesIndexFilter>(key);
          return std::move(pkb->Uses(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::UsesData data) {
          for (auto child : data.get_control_variables()) {
            result.insert(Entity(child));
          }
        },
        results);
  }
};

}  // namespace qps
