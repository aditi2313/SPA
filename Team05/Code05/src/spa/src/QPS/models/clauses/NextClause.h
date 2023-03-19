#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::NextIndexFilter;

namespace qps {
// RS between statements
class NextClause : public Clause {
 public:
  NextClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause
            (ClauseType::kNext, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    Clause::Index<pkb::NextData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<NextIndexFilter>(key);
          return std::move(pkb->Next(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::NextData data) {
          AddList(data.get_next_im_list(), result);
        },
        results);
  }
};
}  // namespace qps
