#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtVarFactory.h"

namespace qps {
class UsesFactory : public StmtVarFactory {
 public:
  UsesFactory() : StmtVarFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

}  // namespace qps
