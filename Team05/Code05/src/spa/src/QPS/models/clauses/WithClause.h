#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/Export.h"

using filter::NextIndexFilter;

namespace qps {
// RS between attrRef
class WithClause : public Clause {
 public:
  WithClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(ClauseType::kWith, std::move(arg1), std::move(arg2)) {}

  void Preprocess(
      pkb::PKBReadPtr &pkb,
      Table &query_table) override;

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    // Just return itself
    results.insert(index);
  }
};
}  // namespace qps
