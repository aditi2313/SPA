#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/Export.h"

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
    filter::FollowsIndexFilter filter(index.get_int());
    auto& follows_reader = pkb->Follows(filter);
    if (follows_reader.reached_end()) return;
    auto &data = follows_reader.read_data();
    AddList(data.get_follows_list(), results);
  }
};
}  // namespace qps
