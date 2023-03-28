#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "ReversableClause.h"
#include "common/filter/filters/Export.h"

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
    filter::FollowsIndexFilter filter(index.get_int());
    auto& follows_reader = pkb->Follows(filter);
    if (follows_reader.reached_end()) return;
    auto& data = follows_reader.read_data();
    results.insert(Entity(data.get_follows()));    
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
