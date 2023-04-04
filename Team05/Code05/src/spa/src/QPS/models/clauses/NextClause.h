#pragma once

#include <memory>
#include <utility>

#include "common/filter/filters/Export.h"
#include "ReversibleClause.h"

using filter::NextIndexFilter;

namespace qps {
// RS between statements
class NextClause : public ReversibleClause {
 public:
  NextClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause
            (ClauseType::kNext, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    filter::NextIndexFilter filter(index.get_int());
    auto &reader = pkb->Next(filter);
    if (reader.reached_end()) return;
    auto &data = reader.read_data();
    AddList(data.get_next_im_list(), results);
  }
  inline void ReverseIndex(
    const Entity& index,
    const pkb::PKBReadPtr& pkb,
    EntitySet& results) override {
    filter::ReverseNextFilter filter(index.get_int());
    auto &reader = pkb->Next(filter);
    WriteSecondIndexesFromReader(reader, results);
  }
};
}  // namespace qps
