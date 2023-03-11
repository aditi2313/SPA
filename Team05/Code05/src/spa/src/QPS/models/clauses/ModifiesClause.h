#pragma once

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::ModifiesIndexFilter;

namespace qps {
// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kModifiesRelName;
  }

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::ModifiesData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<ModifiesIndexFilter>(key);
          return std::move(pkb->Modifies(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::ModifiesData data) {
          for (auto var : data.get_variables()) {
            result.insert(Entity(var));
          }
        },
        results);
  }
};

}  // namespace qps
