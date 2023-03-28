#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ParentIndexFilter;

namespace qps {
// RS between statements (transitive)
class ParentTClause : public Clause {
 public:
  ParentTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kParentT, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    filter::ParentDIndexFilter filter(index.get_int());
    auto& result = pkb->Parent(filter);
    if (result.reached_end()) return;
    auto& data = result.read_data();
    AddList(data.get_all_children(), results);
  }
};

}  // namespace qps
