#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ParentIndexFilter;

namespace qps {
// RS between statements
class ParentClause : public Clause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kParent, std::move(arg1), std::move(arg2)) {}

  inline void Index(const Entity &index,
                    const pkb::PKBReadPtr &pkb,
                    EntitySet &results) override {
    Clause::Index<pkb::ParentData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<ParentIndexFilter>(key);
          return std::move(pkb->Parent(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::ParentData data) {
          for (auto child : data.get_direct_children()) {
            result.insert(Entity(child));
          }
        },
        results);
  }
};

}  // namespace qps
