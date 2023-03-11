#pragma once

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::CallsIndexFilter;

namespace qps {
// RS between procedures
class CallsClause : public Clause {
 public:
  CallsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kCallsRelName;
  }

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    Clause::Index<pkb::CallsData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<CallsIndexFilter>(key);
          return std::move(pkb->Calls(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::CallsData data) {
          for (auto child : data.get_direct_calls()) {
            result.insert(Entity(child));
          }
        },
        results);
  }
};

}  // namespace qps
