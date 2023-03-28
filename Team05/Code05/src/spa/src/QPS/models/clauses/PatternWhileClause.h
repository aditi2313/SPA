#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/Export.h"

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
    ConditionIndexFilter filter(index.get_value());
    auto& reader = pkb->Condition(filter);
    if (reader.reached_end()) return;
    auto &data = reader.read_data();
    AddList(data.get_variables(), results);
  }
};

}  // namespace qps
