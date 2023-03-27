#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ClauseFactory.h"

namespace qps {
class StmtStmtFactory : public ClauseFactory {
 public:
  StmtStmtFactory() : ClauseFactory() {
    LHS_entity_types_ = Entity::get_all_stmt_entities();
    RHS_entity_types_ = Entity::get_all_stmt_entities();
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return MakeClause(std::move(arg1), std::move(arg2));
  }

  virtual ClausePtr MakeClause(ArgumentPtr arg1, ArgumentPtr arg2) = 0;
};
}  // namespace qps
