#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include "Argument.h"
#include "PKB/PKBRead.h"
#include "QPS/factories/MasterEntityFactory.h"
#include "common/filter/filters/PredicateFilter.h"
#include "QueryResult.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  Clause(ArgumentPtr arg1, ArgumentPtr arg2, EntityName LHS, EntityName RHS) :
      arg1_(std::move(arg1)), arg2_(std::move(arg2)), LHS_(LHS), RHS_(RHS) {}
  virtual ~Clause() = 0;

  virtual void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) = 0;

  template<class Data>
  static void Index(
      const Entity &index,
      std::function
          <std::unique_ptr<pkb::IndexableTable<Data>>(int)> pkb_read_function,
      std::function<void(EntitySet &, Data)> add_function,
      EntitySet &results);

  inline virtual void Filter(
      const Entity &index,
      const EntitySet &filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) {
    EntitySet index_results;
    Index(index, pkb, index_results);
    for (auto &entity : index_results) {
      for (auto &filter_entity : filter_values) {
        if (entity.WeakEqual(filter_entity)) {
          results.insert(entity);
        }
      }
    }
  }

  inline virtual void SymmetricFilter(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) {
    EntitySet index_results;
    Index(index, pkb, index_results);
    for (auto &entity : index_results) {
      if (entity.WeakEqual(index)) {
        results.insert(entity);
      }
    }
  }

  bool operator==(Clause const &other) const {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);

    return ti1 == ti2 && *arg1_ == *other.arg1_
        && *arg2_ == *other.arg2_;
  }

  inline bool operator!=(Clause const &other) const {
    return !(*this == other);
  }

  inline ArgumentPtr &get_arg1() { return arg1_; }
  inline ArgumentPtr &get_arg2() { return arg2_; }
  inline EntityName LHS() { return LHS_; }
  inline EntityName RHS() { return RHS_; }
  virtual inline bool IsExactType() { return false; }
  virtual inline bool IsWildcardAllowedAsFirstArg() { return true; }

 protected:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  EntityName LHS_;
  EntityName RHS_;
};

// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kVariableEntityName) {}

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  inline bool IsWildcardAllowedAsFirstArg() override { return false; };
};

// RS between statements
class FollowsClause : public Clause {
 public:
  FollowsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kStmtEntityName) {}

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

// RS between statements (transitive)
class FollowsTClause : public Clause {
 public:
  FollowsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kStmtEntityName) {}

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

class PatternClause : public Clause {
 public:
  PatternClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kAssignEntityName, PQL::kAssignEntityName) {}

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  void Filter(
      const Entity &index,
      const EntitySet &RHS_filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  inline bool IsExactType() override { return true; };
};

// Relationship between a stmt and a variable or vector of variables
class UsesClause : public Clause {
 public:
  UsesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kVariableEntityName) {}

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;

  inline bool IsWildcardAllowedAsFirstArg() override { return false; };
};

// Relationship between a stmt and another stmt.
class ParentClause : public Clause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kStmtEntityName) {}

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class ParentTClause : public Clause {
 public:
  ParentTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kStmtEntityName) {}

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

using ClausePtr = std::unique_ptr<Clause>;

}  // namespace qps
