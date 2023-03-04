#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <iostream>

#include "QPS/models/Clause.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ClauseFactory {
 public:
  ClauseFactory() {}
  virtual ClausePtr Create(
      ArgumentPtr arg1, ArgumentPtr arg2) = 0;

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) {
    if (!is_wildcard_allowed_as_first_arg_ && arg1->IsWildcard()) {
      return false;
    }

    return arg1->Validate(LHS_entity_names_)
        && arg2->Validate(RHS_entity_names_);
  }

  virtual ~ClauseFactory() = default;

 protected:
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
    arg2->set_entity_name(PQL::kVariableEntityName);

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
    arg1->set_entity_name(PQL::kStmtEntityName);
    arg2->set_entity_name(PQL::kStmtEntityName);

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
    arg1->set_entity_name(PQL::kStmtEntityName);
    arg2->set_entity_name(PQL::kStmtEntityName);

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
    arg1->set_entity_name(PQL::kStmtEntityName);
    arg2->set_entity_name(PQL::kStmtEntityName);

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
    arg1->set_entity_name(PQL::kStmtEntityName);
    arg2->set_entity_name(PQL::kStmtEntityName);

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
    arg2->set_entity_name(PQL::kVariableEntityName);

    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternFactory : public ClauseFactory {
 public:
  PatternFactory() : ClauseFactory() {
    LHS_entity_names_.insert(PQL::kAssignEntityName);  // Assign only
  }

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    arg1->set_entity_name(PQL::kAssignEntityName);

    return std::make_unique<PatternClause>(
        std::move(arg1), std::move(arg2));
  }
};

using ClauseFactoryPtr = std::unique_ptr<ClauseFactory>;
}  // namespace qps
