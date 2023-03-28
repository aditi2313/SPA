#pragma once

#include <memory>
#include <string>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/double_index/Export.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between procedures
class CallsClause : public Clause {
 public:
  CallsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(ClauseType::kCalls, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index, const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto key = index.get_value();
    auto callee = std::get<std::string>(key);
    auto &table =
        pkb->Calls(filter::CallsDIndexFilter::of(std::get<std::string>(key)));
    if (table.reached_end()) return;
    auto &data = table.read_data();
    AddList(data.get_direct_calls(), results);
  }
};

}  // namespace qps
