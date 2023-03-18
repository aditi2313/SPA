#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include "PKB/PKBRead.h"
#include "common/filter/filters/PredicateFilter.h"
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

  virtual void Preprocess(
      const pkb::PKBReadPtr &pkb,
      Table &query_table) {
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
          <std::unique_ptr<pkb::IndexableTable<Data>>(
              Entity::Value)> pkb_read_function,
      std::function<void(EntitySet &, Data)> add_function,
      EntitySet &results) {
    Entity::Value key = index.get_value();
    auto pkb_res = pkb_read_function(key);
    if (pkb_res->empty()) return;
    Data data = pkb_res->get_row(key);
    add_function(results, data);
  }

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

  inline ArgumentPtr &get_arg1() { return arg1_; }
  inline ArgumentPtr &get_arg2() { return arg2_; }
  inline ClauseType get_clause_type() { return clause_type_; }

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

 protected:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ClauseType clause_type_;
};

using ClausePtr = std::unique_ptr<Clause>;
}  // namespace qps
