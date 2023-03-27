#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ModifiesIndexFilter;

namespace qps {
// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kModifies, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::ModifiesData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<ModifiesIndexFilter>(key);
          return std::move(pkb->Modifies(std::move(filter)));
        },
        [&](EntitySet &result, pkb::ModifiesData data) {
          AddList(data.get_variables(), result);
        },
        results);
  }
};

}  // namespace qps
