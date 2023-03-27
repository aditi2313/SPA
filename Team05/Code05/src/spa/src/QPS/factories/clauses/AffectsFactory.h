#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"
#include "StmtStmtFactory.h"

namespace qps {
class AffectsFactory : public StmtStmtFactory {
 public:
  AffectsFactory() : StmtStmtFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<AffectsClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
