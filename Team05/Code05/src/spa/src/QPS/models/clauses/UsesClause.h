#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::UsesIndexFilter;

namespace qps {
// RS between a statement and a list of variables
class UsesClause : public Clause {
 public:
  UsesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kUses, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    UsesIndexFilter filter(index.get_value());
    auto& reader = pkb->Uses(filter);
    if (reader.reached_end()) return;
    AddList(reader.read_data().get_variables(), results);
  }
};
}  // namespace qps
