#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class PatternWhileFactory : public ClauseFactory {
public:
  PatternWhileFactory() : ClauseFactory() {
      LHS_entity_types_.insert(EntityType::kWhile);  // While only
      RHS_entity_types_.insert(EntityType::kVariable);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
      InitializeWildcard(arg2, EntityType::kVariable);

      return std::make_unique<PatternWhileClause>(std::move(arg1),
                                                  std::move(arg2));
  }
};

}  // namespace qps
