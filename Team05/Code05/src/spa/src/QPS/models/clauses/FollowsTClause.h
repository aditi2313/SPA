#pragma once

#include <memory>
#include <utility>

#include "TClause.h"
#include "common/filter/filters/Export.h"

using filter::FollowsIndexFilter;

namespace qps {
// RS between statements (transitive)
class FollowsTClause : public TClause {
 public:
  FollowsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : TClause(
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

  bool TIndex(const Entity& index, const pkb::PKBReadPtr& pkb,
    const Entity& reference) override {
    filter::FollowsIndexFilter filter(index.get_int());
    auto& reader = pkb->Follows(filter);
    if (reader.reached_end()) return false;
    auto& data = reader.read_data();
    return data.get_follows_list().count(reference.get_int());
  }
};
}  // namespace qps
