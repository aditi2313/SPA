#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "StmtStmtClauseFactory.h"

namespace qps {
class FollowsTFactory : public StmtStmtClauseFactory {
 public:
  FollowsTFactory() : StmtStmtClauseFactory() {
    LHS_entity_types_ = Entity::get_all_stmt_entities();
    RHS_entity_types_ = Entity::get_all_stmt_entities();
  }

  inline ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<FollowsTClause>(
        std::move(arg1), std::move(arg2));
  }
};
}  // namespace qps
