#pragma once

#include <memory>
#include <string>
#include <utility>

#include "ReversibleClause.h"
#include "common/filter/filters/Export.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between procedures
class CallsClause : public ReversibleClause {
 public:
  CallsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : ReversibleClause(ClauseType::kCalls, std::move(arg1), std::move(arg2)) {
  }

  inline void Index(const Entity &index, const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    auto key = index.get_value();
    auto callee = std::get<std::string>(key);
    auto filter = filter::CallsIndexFilter(std::get<std::string>(key));
    auto &table = pkb->Calls(filter);
    if (table.reached_end()) return;
    auto &data = table.read_data();
    AddList(data.get_direct_calls(), results);
  }

  void ReverseIndex(const Entity &index, const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    filter::ReverseCallsFilter filter(index.get_str());
    auto &reader = pkb->Calls(filter);
    WriteSecondIndexesFromReader(reader, results);
  }
};

}  // namespace qps
