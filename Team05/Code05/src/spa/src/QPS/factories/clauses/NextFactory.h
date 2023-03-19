#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class NextFactory : public ClauseFactory {
 public:
  NextFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<NextClause>(std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
