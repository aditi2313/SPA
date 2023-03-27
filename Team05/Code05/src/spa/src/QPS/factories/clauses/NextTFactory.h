#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtStmtFactory.h"

namespace qps {
class NextTFactory : public StmtStmtFactory {
 public:
  NextTFactory() : StmtStmtFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<NextTClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
