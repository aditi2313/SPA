#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class NextFactory : public StmtStmtFactory {
 public:
  NextFactory() : StmtStmtFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<NextClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
