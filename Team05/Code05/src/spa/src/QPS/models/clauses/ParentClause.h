#pragma once

#include <memory>
#include <utility>

#include "ReversibleClause.h"
#include "common/filter/filters/Export.h"

using filter::ParentIndexFilter;

namespace qps {
// RS between statements
class ParentClause : public ReversibleClause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause(
      ClauseType::kParent, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    filter::ParentIndexFilter filter(index.get_int());
    auto& result = pkb->Parent(filter);
    if (result.reached_end()) return;
    auto& data = result.read_data();
    AddList(data.get_direct_children(), results);
  }

  inline void ReverseIndex(
    const Entity& index,
    const pkb::PKBReadPtr& pkb,
    EntitySet& results) override {
    filter::ReverseParentFilter filter(index.get_int());
    auto& reader = pkb->Parent(filter);
    WriteSecondIndexesFromReader(reader, results);
  }
};

}  // namespace qps
