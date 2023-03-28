#pragma once

#include <memory>
#include <utility>

#include "ReversableClause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ParentIndexFilter;

namespace qps {
// RS between statements
class ParentClause : public ReversableClause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversableClause(
      ClauseType::kParent, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    Clause::Index<pkb::ParentData>(
        index,
        [&](Entity::Value key) {
          filter::ParentDIndexFilter filter(index.get_int());
          return std::move(pkb->Parent(filter));
        },
        [&](EntitySet &result, pkb::ParentData data) {
          AddList(data.get_direct_children(), result);
        },
        results);
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
