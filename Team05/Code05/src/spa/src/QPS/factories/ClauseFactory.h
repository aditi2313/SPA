#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>

#include "QPS/models/Clause.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ClauseFactory {
 public:
  ClauseFactory() {}
  virtual ClausePtr Create(
      ArgumentPtr arg1, ArgumentPtr arg2) = 0;

  virtual bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) = 0;

  virtual ~ClauseFactory() = default;
};

class ModifiesFactory : public ClauseFactory {
 public:
  ModifiesFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ModifiesClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsEntRef();
  }
};

class FollowsFactory : public ClauseFactory {
 public:
  FollowsFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<FollowsClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsStmtRef();
  }
};

class FollowsTFactory : public ClauseFactory {
 public:
  FollowsTFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<FollowsTClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsStmtRef();
  }
};

class ParentFactory : public ClauseFactory {
 public:
  ParentFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsStmtRef();
  }
};

class ParentTFactory : public ClauseFactory {
 public:
  ParentTFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentTClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsStmtRef();
  }
};

class UsesFactory : public ClauseFactory {
 public:
  UsesFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsStmtRef() && arg2->IsEntRef();
  }
};

class PatternFactory : public ClauseFactory {
 public:
  PatternFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<PatternClause>(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(ArgumentPtr &arg1, ArgumentPtr &arg2) override {
    return arg1->IsSynonym() && arg2->IsExpression();
  }
};

using ClauseFactoryPtr = std::unique_ptr<ClauseFactory>;
}  // namespace qps
