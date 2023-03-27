#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtVarClauseFactory.h"

namespace qps {
class UsesFactory : public StmtVarClauseFactory {
 public:
  UsesFactory() : StmtVarClauseFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

}  // namespace qps
