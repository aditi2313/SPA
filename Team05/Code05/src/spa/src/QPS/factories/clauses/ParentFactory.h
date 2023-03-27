#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtStmtClauseFactory.h"

namespace qps {
class ParentFactory : public StmtStmtClauseFactory {
 public:
  ParentFactory() : StmtStmtClauseFactory() {}

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
