#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include "QPS/models/arguments/Export.h"
#include "PKB/PKBRead.h"
#include "QPS/factories/MasterEntityFactory.h"
#include "common/filter/filters/PredicateFilter.h"
#include "QueryResult.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  Clause(ArgumentPtr arg1, ArgumentPtr arg2) :
      arg1_(std::move(arg1)), arg2_(std::move(arg2)) {}
  virtual ~Clause() = 0;

  virtual void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) = 0;

  template<class Data>
  static void Index(
      const Entity &index,
      std::function
          <std::unique_ptr<pkb::IndexableTable<Data>>(
              Entity::Value)> pkb_read_function,
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

  inline bool operator==(Clause const &other) const {
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
  inline RelName get_rel_name() { return rel_name_; }

 protected:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  RelName rel_name_;
};

// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kModifiesRelName;
  }

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

// RS between statements
class FollowsClause : public Clause {
 public:
  FollowsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kFollowsRelName;
  }

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

// RS between statements (transitive)
class FollowsTClause : public Clause {
 public:
  FollowsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kFollowsRelName;
  }

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

class PatternClause : public Clause {
 public:
  PatternClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kPatternRelName;
  }

  void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  void Filter(
      const Entity &index,
      const EntitySet &RHS_filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override;
};

// Relationship between a stmt and a variable or vector of variables
class UsesClause : public Clause {
 public:
  UsesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kUsesRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

// Relationship between a stmt and another stmt.
class ParentClause : public Clause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kParentRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class ParentTClause : public Clause {
 public:
  ParentTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kParentTRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class CallsClause : public Clause {
 public:
  CallsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kCallsRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class CallsTClause : public Clause {
 public:
  CallsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kCallsTRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class NextClause : public Clause {
 public:
  NextClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kNextRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

class WithClause : public Clause {
 public:
  WithClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kWithRelName;
  }

  void Index(const Entity &index,
             const pkb::PKBReadPtr &pkb,
             EntitySet &results) override;
};

using ClausePtr = std::unique_ptr<Clause>;

}  // namespace qps
