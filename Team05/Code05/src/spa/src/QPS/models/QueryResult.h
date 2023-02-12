#pragma once

#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory>

#include "models/Entity.h"
#include "QPS/evaluator/EntityFactory.h"

namespace qps {
class QueryResult {
 public:
  QueryResult() {}
  virtual ~QueryResult() = 0;
  virtual inline bool IsBoolean() { return false; }
};

class ListQueryResult : public QueryResult {
 public:
  ListQueryResult() {}

  explicit ListQueryResult(EntityPtrList &entities): QueryResult() {
    for (auto &entity : entities) {
      query_results_.push_back(std::move(entity));
    }
  }

  inline std::vector<models::EntityPtr> &get_query_results() {
    return query_results_;
  }

  inline void add_query_result(EntityPtr &&entity) {
    query_results_.push_back(std::move(entity));
  }

  inline bool is_empty() { return query_results_.empty(); }

  inline void clear() { query_results_.clear(); }

  void IntersectWith(ListQueryResult &other_result);

  inline void Sort() {
    std::sort(query_results_.begin(), query_results_.end(),
              [](EntityPtr const &LHS, EntityPtr const &RHS) {
                return *LHS < *RHS;
              });
  }

 private:
  EntityPtrList query_results_;
};

class BoolQueryResult : public QueryResult {
 public:
  explicit BoolQueryResult(bool is_true) :
    QueryResult(), is_true_(is_true) {}

    inline bool IsBoolean() override { return true; }
    inline bool IsTrue() { return is_true_; }

 private:
  bool is_true_;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;
using ListQueryResultPtr = std::unique_ptr<ListQueryResult>;
}  // namespace qps
