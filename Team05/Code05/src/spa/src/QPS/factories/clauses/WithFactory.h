#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class WithFactory : public ClauseFactory {
public:
  WithFactory() : ClauseFactory() {
      LHS_entity_types_ = PQL::kAllEntityTypes;
      RHS_entity_types_ = PQL::kAllEntityTypes;
  }

  // Also check if the type of the LHS and RHS matches
  // i.e both numbers (stmt.stmt# = 12) or
  // both names (var.varName = "var")
  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
      // Mismatched LHS and RHS types (e.g stmt.stmt# = "string")
      if ((arg1->IsIdentType() && arg2->IsIntegerType()) ||
          (arg1->IsIntegerType() && arg2->IsIdentType()))
          return false;

      return arg1->Validate(LHS_entity_types_) &&
          arg2->Validate(RHS_entity_types_);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
      return std::make_unique<WithClause>(std::move(arg1), std::move(arg2));
  }
};

}  // namespace qps
