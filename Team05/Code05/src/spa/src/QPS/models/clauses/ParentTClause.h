#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/Export.h"

using filter::ParentIndexFilter;

namespace qps {
// RS between statements (transitive)
class ParentTClause : public TClause {
 public:
  ParentTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : TClause(
      ClauseType::kParentT, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    filter::ParentIndexFilter filter(index.get_int());
    auto& result = pkb->Parent(filter);
    if (result.reached_end()) return;
    auto& data = result.read_data();
    AddList(data.get_all_children(), results);
  }
  bool TIndex(const Entity &index, const pkb::PKBReadPtr &pkb,
                      const Entity &reference) override {
    auto filter = filter::ParentIndexFilter(index.get_int());
    auto &reader = pkb->Parent(filter);
    if (reader.reached_end()) return false;
    auto &data = reader.read_data();
    auto &calls = data.get_all_children();
    return calls.count(reference.get_int());
  }
};
}  // namespace qps
