#pragma once

#include <vector>
#include <unordered_set>
#include <utility>
#include <string>
#include <memory>
#include <iostream>

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

    return arg1->Validate(LHS_entity_names_)
        && arg2->Validate(RHS_entity_names_);
  }

  virtual ~ClauseFactory() = default;

 protected:
  void InitializeWildcard(ArgumentPtr &arg, EntityName entity_name_) {
    if (!arg->IsWildcard()) return;
    Wildcard *wildcard = dynamic_cast<Wildcard *>(arg.get());
    wildcard->set_entity_name(entity_name_);
  }

  std::unordered_set<std::string> LHS_entity_names_;
  std::unordered_set<std::string> RHS_entity_names_;
  bool is_wildcard_allowed_as_first_arg_ = true;
};

class ModifiesFactory : public ClauseFactory {
 public:
  ModifiesFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    LHS_entity_names_.insert(PQL::kProcedureEntityName);
    RHS_entity_names_.insert(PQL::kVariableEntityName);
    is_wildcard_allowed_as_first_arg_ = false;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    // Note: arg1 cannot be wildcard
    InitializeWildcard(arg2, PQL::kVariableEntityName);

    return std::make_unique<ModifiesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsFactory : public ClauseFactory {
 public:
  FollowsFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    RHS_entity_names_ = PQL::kAllStmtEntityNames;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kStmtEntityName);
    InitializeWildcard(arg2, PQL::kStmtEntityName);

    return std::make_unique<FollowsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsTFactory : public ClauseFactory {
 public:
  FollowsTFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    RHS_entity_names_ = PQL::kAllStmtEntityNames;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kStmtEntityName);
    InitializeWildcard(arg2, PQL::kStmtEntityName);

    return std::make_unique<FollowsTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentFactory : public ClauseFactory {
 public:
  ParentFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    RHS_entity_names_ = PQL::kAllStmtEntityNames;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kStmtEntityName);
    InitializeWildcard(arg2, PQL::kStmtEntityName);

    return std::make_unique<ParentClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentTFactory : public ClauseFactory {
 public:
  ParentTFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    RHS_entity_names_ = PQL::kAllStmtEntityNames;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kStmtEntityName);
    InitializeWildcard(arg2, PQL::kStmtEntityName);

    return std::make_unique<ParentTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class UsesFactory : public ClauseFactory {
 public:
  UsesFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    LHS_entity_names_.insert(PQL::kProcedureEntityName);
    RHS_entity_names_.insert(PQL::kVariableEntityName);
    is_wildcard_allowed_as_first_arg_ = false;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    // Note: arg1 cannot be wildcard
    InitializeWildcard(arg2, PQL::kVariableEntityName);

    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternAssignFactory : public ClauseFactory {
 public:
  PatternAssignFactory() : ClauseFactory() {
    LHS_entity_names_.insert(PQL::kAssignEntityName);  // Assign only
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kAssignEntityName);

    return std::make_unique<PatternAssignClause>(
        std::move(arg1), std::move(arg2));
  }
};

class CallsFactory : public ClauseFactory {
 public:
  CallsFactory() : ClauseFactory() {
    LHS_entity_names_.insert(PQL::kProcedureEntityName);
    RHS_entity_names_.insert(PQL::kProcedureEntityName);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kProcedureEntityName);
    InitializeWildcard(arg2, PQL::kProcedureEntityName);

    return std::make_unique<CallsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class CallsTFactory : public ClauseFactory {
 public:
  CallsTFactory() : ClauseFactory() {
    LHS_entity_names_.insert(PQL::kProcedureEntityName);
    RHS_entity_names_.insert(PQL::kProcedureEntityName);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kProcedureEntityName);
    InitializeWildcard(arg2, PQL::kProcedureEntityName);

    return std::make_unique<CallsTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class NextFactory : public ClauseFactory {
 public:
  NextFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllStmtEntityNames;
    RHS_entity_names_ = PQL::kAllStmtEntityNames;
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    InitializeWildcard(arg1, PQL::kStmtEntityName);
    InitializeWildcard(arg2, PQL::kStmtEntityName);

    return std::make_unique<NextClause>(
        std::move(arg1), std::move(arg2));
  }
};

class WithFactory : public ClauseFactory {
 public:
  WithFactory() : ClauseFactory() {
    LHS_entity_names_ = PQL::kAllEntityNames;
    RHS_entity_names_ = PQL::kAllEntityNames;
  }

  // Also check if the type of the LHS and RHS matches
  // i.e both numbers (stmt.stmt# = 12) or
  // both names (var.varName = "var")
  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    // Mismatched LHS and RHS types (e.g stmt.stmt# = "string")
    if ((arg1->IsIdentType() && arg2->IsIntegerType())
        || (arg1->IsIntegerType() && arg2->IsIdentType()))
      return false;

    return arg1->Validate(LHS_entity_names_)
        && arg2->Validate(RHS_entity_names_);
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<WithClause>(
        std::move(arg1), std::move(arg2));
  }
};

using ClauseFactoryPtr = std::unique_ptr<ClauseFactory>;
}  // namespace qps
