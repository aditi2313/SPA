#pragma once

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::NextIndexFilter;

namespace qps {
// RS between attrRef
class WithClause : public Clause {
 public:
  WithClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kWithRelName;
  }

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    // Just return itself
    results.insert(index);
  }
};
}  // namespace qps
