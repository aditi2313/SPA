#pragma once

#include <memory>
#include <utility>
#include <string>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/double_index/Export.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between procedures (transitive)
class CallsTClause : public Clause {
 public:
  CallsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kCallsT, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto key = index.get_value();
    auto callee = std::get<std::string>(key);
    auto &table =
        pkb->Calls(filter::CallsDIndexFilter::of(std::get<std::string>(key)));
    if (table.reached_end()) return;
    auto &data = table.read_data();
    AddList(data.get_total_calls(), results);
  }
};

}  // namespace qps
