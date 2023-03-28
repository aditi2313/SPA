#pragma once

#include <memory>
#include <utility>

#include "common/filter/filters/IndexFilter.h"
#include "ReversableClause.h"

using filter::NextIndexFilter;

namespace qps {
// RS between statements
class NextClause : public ReversableClause {
 public:
  NextClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversableClause
            (ClauseType::kNext, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    NextIndexFilter filter(index.get_int());
    auto &reader = pkb->Next(filter);
    if (reader.reached_end()) return;
    AddList(reader.read_data().get_next_im_list(), results);
  }

  
  inline virtual void ReverseIndex(const Entity& index,
    const pkb::PKBReadPtr& pkb,
    EntitySet& results) {
    filter::ReverseNextFilter filter(index.get_int());    
    auto &reader = pkb->Next(filter);    
    WriteSecondIndexesFromReader(reader, results);
  }
};
}  // namespace qps
