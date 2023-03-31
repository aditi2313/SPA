#pragma once

#include <memory>
#include <utility>
#include <string>
#include <iostream>

#include "TClause.h"
#include "common/filter/filters/Export.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between procedures (transitive)
class CallsTClause : public TClause {
 public:
  CallsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : TClause(
      ClauseType::kCallsT, std::move(arg1), std::move(arg2)) {
  }

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto key = index.get_value();
    auto callee = std::get<std::string>(key);
    auto filter = filter::CallsIndexFilter(std::get<std::string>(key));
    auto &table =
        pkb->Calls(filter);
    if (table.reached_end()) return;
    auto &data = table.read_data();
    AddList(data.get_total_calls(), results);
  }

  bool TIndex(const Entity &index, const pkb::PKBReadPtr &pkb,
                      const Entity &reference) override {
    auto filter = filter::CallsIndexFilter(index.get_str());
    auto &reader = pkb->Calls(filter);
    if (reader.reached_end()) return false;
    auto &data = reader.read_data();
    auto &calls = data.get_total_calls();
    return calls.count(reference.get_str());
  }
};

}  // namespace qps
