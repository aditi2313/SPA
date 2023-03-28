#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "ReversableClause.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/double_index/Export.h"

using filter::FollowsIndexFilter;

namespace qps {
// RS between statements
class FollowsClause : public ReversableClause {
 public:
  FollowsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversableClause(
      ClauseType::kFollows, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    FollowsIndexFilter filter(index.get_int());
    auto& follows_reader = pkb->Follows(filter);
    if (follows_reader.reached_end()) return;
    AddList(follows_reader.read_data().get_follows(), results);
  }

  inline void ReverseIndex(
    const Entity& index,
    const pkb::PKBReadPtr& pkb,
    EntitySet& results) override {
    filter::ReverseFollowFilter filter(index.get_int());    
    auto& reader = pkb->Follows(filter);
    WriteSecondIndexesFromReader(reader, results);
  }
};
}  // namespace qps
