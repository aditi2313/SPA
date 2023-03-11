#pragma once

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::NextIndexFilter;

namespace qps {
// RS between statements
class NextClause : public Clause {
 public:
  NextClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kNextRelName;
  }

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
          for (auto child : data.get_next_im_list()) {
            result.insert(Entity(child));
          }
        },
        results);
  }
};
}  // namespace qps
