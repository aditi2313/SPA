#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "QPS/models/clauses/Export.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ClauseFactory {
 public:
  ClauseFactory() {}
  virtual ClausePtr Create(
      ArgumentPtr arg1, ArgumentPtr arg2) = 0;

  inline virtual bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) {
    if (!is_wildcard_allowed_as_first_arg_ && arg1->IsWildcard()) {
      return false;
    }

    return arg1->Validate(LHS_entity_types_)
        && arg2->Validate(RHS_entity_types_);
  }

  virtual ~ClauseFactory() = default;

 protected:
  void InitializeWildcard(ArgumentPtr &arg, EntityType entity_type) {
    if (!arg->IsWildcard()) return;
    Wildcard *wildcard = dynamic_cast<Wildcard *>(arg.get());
    wildcard->set_entity_type(entity_type);
  }

  std::unordered_set<EntityType> LHS_entity_types_;
  std::unordered_set<EntityType> RHS_entity_types_;
  bool is_wildcard_allowed_as_first_arg_ = true;
};

class AffectsFactory : public ClauseFactory {
 public:
  AffectsFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<AffectsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ModifiesFactory : public ClauseFactory {
 public:
  ModifiesFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    LHS_entity_types_.insert(EntityType::kProcedure);
    RHS_entity_types_.insert(EntityType::kVariable);
    is_wildcard_allowed_as_first_arg_ = false;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    // Note: arg1 cannot be wildcard
    InitializeWildcard(arg2, EntityType::kVariable);

    return std::make_unique<ModifiesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsFactory : public ClauseFactory {
 public:
  FollowsFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<FollowsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsTFactory : public ClauseFactory {
 public:
  FollowsTFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<FollowsTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentFactory : public ClauseFactory {
 public:
  ParentFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<ParentClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentTFactory : public ClauseFactory {
 public:
  ParentTFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<ParentTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class UsesFactory : public ClauseFactory {
 public:
  UsesFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    LHS_entity_types_.insert(EntityType::kProcedure);
    RHS_entity_types_.insert(EntityType::kVariable);
    is_wildcard_allowed_as_first_arg_ = false;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    // Note: arg1 cannot be wildcard
    InitializeWildcard(arg2, EntityType::kVariable);

    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternAssignFactory : public ClauseFactory {
 public:
  PatternAssignFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kAssign);  // Assign only
    RHS_entity_types_.insert(EntityType::kVariable);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg2, EntityType::kVariable);

    return std::make_unique<PatternAssignClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternIfFactory : public ClauseFactory {
 public:
  PatternIfFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kIf);  // If only
    RHS_entity_types_.insert(EntityType::kVariable);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<PatternIfClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternWhileFactory : public ClauseFactory {
 public:
  PatternWhileFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kWhile);  // While only
    RHS_entity_types_.insert(EntityType::kVariable);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg2, EntityType::kVariable);

    return std::make_unique<PatternWhileClause>(
        std::move(arg1), std::move(arg2));
  }
};

class CallsFactory : public ClauseFactory {
 public:
  CallsFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kProcedure);
    RHS_entity_types_.insert(EntityType::kProcedure);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kProcedure);
    InitializeWildcard(arg2, EntityType::kProcedure);

    return std::make_unique<CallsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class CallsTFactory : public ClauseFactory {
 public:
  CallsTFactory() : ClauseFactory() {
    LHS_entity_types_.insert(EntityType::kProcedure);
    RHS_entity_types_.insert(EntityType::kProcedure);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kProcedure);
    InitializeWildcard(arg2, EntityType::kProcedure);

    return std::make_unique<CallsTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class NextFactory : public ClauseFactory {
 public:
  NextFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<NextClause>(
        std::move(arg1), std::move(arg2));
  }
};

class NextTFactory : public ClauseFactory {
 public:
  NextTFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllStmtEntityTypes;
    RHS_entity_types_ = PQL::kAllStmtEntityTypes;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, EntityType::kStmt);
    InitializeWildcard(arg2, EntityType::kStmt);

    return std::make_unique<NextTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class WithFactory : public ClauseFactory {
 public:
  WithFactory() : ClauseFactory() {
    LHS_entity_types_ = PQL::kAllEntityTypes;
    RHS_entity_types_ = PQL::kAllEntityTypes;
  }

  // Also check if the type of the LHS and RHS matches
  // i.e both numbers (stmt.stmt# = 12) or
  // both names (var.varName = "var")
  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    // Mismatched LHS and RHS types (e.g stmt.stmt# = "string")
    if ((arg1->IsIdentType() && arg2->IsIntegerType())
        || (arg1->IsIntegerType() && arg2->IsIdentType()))
      return false;

    return arg1->Validate(LHS_entity_types_)
        && arg2->Validate(RHS_entity_types_);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<WithClause>(
        std::move(arg1), std::move(arg2));
  }
};

using ClauseFactoryPtr = std::unique_ptr<ClauseFactory>;
}  // namespace qps
