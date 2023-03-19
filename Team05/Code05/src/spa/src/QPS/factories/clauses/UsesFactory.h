#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class UsesFactory : public ClauseFactory {
public:
  UsesFactory() : ClauseFactory() {
      LHS_entity_types_ = PQL::kAllStmtEntityTypes;
      LHS_entity_types_.insert(EntityType::kProcedure);
      RHS_entity_types_.insert(EntityType::kVariable);
      is_wildcard_allowed_as_first_arg_ = false;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
      // Note: arg1 cannot be wildcard
      InitializeWildcard(arg2, EntityType::kVariable);

      return std::make_unique<UsesClause>(std::move(arg1), std::move(arg2));
  }
};

}  // namespace qps
