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

  virtual ~ClauseFactory() = default;
};

class ModifiesFactory : public ClauseFactory {
 public:
  ModifiesFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ModifiesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsFactory : public ClauseFactory {
 public:
  FollowsFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<FollowsClause>(
        std::move(arg1), std::move(arg2));
  }
};

class FollowsTFactory : public ClauseFactory {
 public:
  FollowsTFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<FollowsTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentFactory : public ClauseFactory {
 public:
  ParentFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentClause>(
        std::move(arg1), std::move(arg2));
  }
};

class ParentTFactory : public ClauseFactory {
 public:
  ParentTFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<ParentTClause>(
        std::move(arg1), std::move(arg2));
  }
};

class UsesFactory : public ClauseFactory {
 public:
  UsesFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<UsesClause>(
        std::move(arg1), std::move(arg2));
  }
};

class PatternFactory : public ClauseFactory {
 public:
  PatternFactory() : ClauseFactory() {}

  inline ClausePtr Create(ArgumentPtr arg1, ArgumentPtr arg2) override {
    return std::make_unique<PatternClause>(
        std::move(arg1), std::move(arg2));
  }
};

using ClauseFactoryPtr = std::unique_ptr<ClauseFactory>;
}  // namespace qps
