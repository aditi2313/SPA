#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <unordered_set>
#include <unordered_map>

#include "PKB/PKBRead.h"
#include "common/filter/filters/Export.h"
#include "QPS/models/arguments/Export.h"
#include "QPS/factories/MasterEntityFactory.h"
#include "QPS/models/QueryResult.h"
#include "ClauseType.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  Clause(ClauseType clause_type, ArgumentPtr arg1, ArgumentPtr arg2)
      : clause_type_(clause_type),
        arg1_(std::move(arg1)),
        arg2_(std::move(arg2)) {}

  inline static ClauseType get_clause_type(RelName const rel_name) {
    return kRelNameToClauseTypeMap.at(rel_name);
  }

  // Returns true if the string is a relationship that appears
  // after such-that.
  // Examples of non such-that rel names are 'pattern' and 'with'
  inline static bool is_such_that_rel_name(std::string const token) {
    return kAllSuchThatRelNames.count(token);
  }

  virtual void Preprocess(
      pkb::PKBReadPtr &pkb,
      Table &query_table,
      bool &is_table_initialized) {
    return;
  }

  virtual void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) = 0;

  template<class Data>
  inline static void Index(
      const Entity &index,
      std::function
          <std::unique_ptr<pkb::TableReader<Data>>(
              Entity::Value)> pkb_read_function,
      std::function<void(EntitySet &, const Data&)> add_function,
      EntitySet &results) {
    Entity::Value key = index.get_value();
    auto reader = pkb_read_function(key);
    if (reader->reached_end()) return;
    const Data& data = reader->read_data();
    add_function(results, data);
  }

  template<class Data>
  inline static void AddList(
      Data &data,
      EntitySet &results) {
    for (auto &value : data) {
      results.insert(Entity(value));
    }
  }

  /// <summary>
  /// Generates the two synonym rows
  /// from the given lhs and rhs.
  /// </summary>
  inline virtual void Filter(
    const EntitySet& lhs,
    const EntitySet& rhs,
    Table::TwoSynonymRows& results_r,
    const pkb::PKBReadPtr& pkb) {
    for (auto &index : lhs) {
      EntitySet results;
      Filter(index, rhs, pkb, results);
      for (auto &result : results) {
        results_r.emplace_back(index, result);
      }
    }
  }

  inline virtual void Filter(
      const Entity &index,
      const EntitySet &filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) {
    EntitySet index_results;
    Index(index, pkb, index_results);
    for (auto &entity : index_results) {
      if (filter_values.count(entity)) {
        results.insert(entity);
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

  inline ArgumentPtr &get_arg1() { return arg1_; }
  inline ArgumentPtr &get_arg2() { return arg2_; }
  inline ClauseType get_clause_type() { return clause_type_; }
  inline bool has_synonym_arg() {
    return arg1_->IsSynonym() || arg2_->IsSynonym();
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

  virtual ~Clause() = default;

  friend class ClauseOptimiser;

 protected:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ClauseType clause_type_;

 private:
  inline static std::unordered_map<RelName, ClauseType> kRelNameToClauseTypeMap{
      {PQL::kAffectsRelName, ClauseType::kAffects},
      {PQL::kAffectsTRelName, ClauseType::kAffectsT},
      {PQL::kModifiesRelName, ClauseType::kModifies},
      {PQL::kFollowsRelName, ClauseType::kFollows},
      {PQL::kFollowsTRelName, ClauseType::kFollowsT},
      {PQL::kPatternRelName, ClauseType::kPatternAssign},
      {PQL::kUsesRelName, ClauseType::kUses},
      {PQL::kParentRelName, ClauseType::kParent},
      {PQL::kParentTRelName, ClauseType::kParentT},
      {PQL::kCallsRelName, ClauseType::kCalls},
      {PQL::kCallsTRelName, ClauseType::kCallsT},
      {PQL::kNextRelName, ClauseType::kNext},
      {PQL::kNextTRelName, ClauseType::kNextT},
      {PQL::kWithRelName, ClauseType::kWith}
  };

  // All relationships that appear after such that
  inline static std::unordered_set<std::string> kAllSuchThatRelNames{
      PQL::kAffectsRelName, PQL::kAffectsTRelName,
      PQL::kCallsRelName, PQL::kCallsTRelName,
      PQL::kFollowsRelName, PQL::kFollowsTRelName,
      PQL::kModifiesRelName,
      PQL::kNextRelName, PQL::kNextTRelName,
      PQL::kParentRelName, PQL::kParentTRelName,
      PQL::kUsesRelName,
  };
};

using ClausePtr = std::unique_ptr<Clause>;
}  // namespace qps
