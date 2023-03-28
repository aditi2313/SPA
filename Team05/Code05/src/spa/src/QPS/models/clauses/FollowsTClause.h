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
          FollowsIndexFilter filter(key);       
          auto& follows_reader = pkb->Follows(filter);
          return std::make_unique<pkb::FollowsDataReader>(follows_reader);
        },
        [&](EntitySet &result, pkb::FollowsData data) {
          AddList(data.get_follows_list(), result);
        },
        results);
  }
};
}  // namespace qps
