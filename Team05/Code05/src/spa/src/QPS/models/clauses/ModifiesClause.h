#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/Export.h"

using filter::ModifiesIndexFilter;

namespace qps {
// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kModifies, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    ModifiesIndexFilter filter(index.get_value());
    auto& reader = pkb->Modifies(filter);
    if (reader.reached_end()) return;
    AddList(reader.read_data().get_variables(), results);
  }
};

}  // namespace qps
