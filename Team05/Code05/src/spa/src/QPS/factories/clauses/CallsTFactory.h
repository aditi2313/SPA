#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class CallsTFactory : public ClauseFactory {
public:
  CallsTFactory() : ClauseFactory() {
      LHS_entity_types_.insert(EntityType::kProcedure);
      RHS_entity_types_.insert(EntityType::kProcedure);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
      InitializeWildcard(arg1, EntityType::kProcedure);
      InitializeWildcard(arg2, EntityType::kProcedure);

      return std::make_unique<CallsTClause>(std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
