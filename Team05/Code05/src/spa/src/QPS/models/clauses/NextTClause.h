#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_set>
#include <utility>

#include "Clause.h"

namespace qps {

class NextTClause : public ReversibleClause {
 public:
  NextTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause(ClauseType::kNextT,
                         std::move(arg1),
                         std::move(arg2)) {}

  inline void Index(const Entity &index, const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    assert(index.is_int());
    auto res = pkb->NextT(index.get_int());
    AddList(res, results);
  }

  inline void ReverseIndex(const Entity &index,
                           const pkb::PKBReadPtr &pkb,
                           EntitySet &results) override {
    assert(index.is_int());
    auto res = pkb->ReverseNextT(index.get_int());
    AddList(res, results);
  }


  inline bool WildcardIndex(const Entity &index,
                            const pkb::PKBReadPtr &pkb) override {
    // Optimisation: instead of performing BFS to get all the line numbers,
    // if we only want to know whether there are results just check NextData
    // since NextData has children <=> NextT results exist
    filter::NextIndexFilter filter(index.get_int());
    auto &reader = pkb->Next(filter);
    return !reader.reached_end();
  }

  inline bool ReverseWildcardIndex(const Entity &index,
                            const pkb::PKBReadPtr &pkb) override {
    // Same optimisation reasoning as above, but reverse
    filter::ReverseNextFilter filter(index.get_int());
    auto &reader = pkb->Next(filter);
    return !reader.reached_end();
  }
};

}  // namespace qps
