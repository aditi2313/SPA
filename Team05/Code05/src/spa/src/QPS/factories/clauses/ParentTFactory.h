#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtStmtFactory.h"

namespace qps {
class ParentTFactory : public StmtStmtFactory {
 public:
  ParentTFactory() : StmtStmtFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentTClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
