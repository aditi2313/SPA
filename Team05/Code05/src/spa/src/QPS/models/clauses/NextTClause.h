#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_set>
#include <utility>

#include "Clause.h"

namespace qps {

class NextTClause : public Clause {
 public:
  NextTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kNextTRelName;
  }

  inline void Index(const Entity& index, const pkb::PKBReadPtr& pkb,
                    EntitySet& results) override {
    assert(index.is_int());
    auto res = pkb->NextT(index.get_int());
    for (auto v : res) {
      results.insert(Entity(v));
    }
  }
};

}  // namespace qps
