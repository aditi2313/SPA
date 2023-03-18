#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::FollowsIndexFilter;

namespace qps {
// RS between statements (transitive)
class FollowsTClause : public Clause {
 public:
  FollowsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kFollowsT, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::FollowsData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<FollowsIndexFilter>(key);
          return std::move(pkb->Follows(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::FollowsData data) {
          for (auto stmt : data.get_follows_list()) {
            result.insert(Entity(stmt));
          }
        },
        results);
  }
};
}  // namespace qps
