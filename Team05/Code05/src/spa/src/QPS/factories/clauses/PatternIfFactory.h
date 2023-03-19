#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {

class PatternIfFactory : public ClauseFactory {
 public:
  PatternIfFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kIf);  // If only
    RHS_entity_types_.insert(EntityType::kVariable);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<PatternIfClause>(std::move(arg1), std::move(arg2));
  }
};

}  // namespace qps
