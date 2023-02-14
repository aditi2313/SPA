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

  explicit QueryResult(EntityPtrList &entities): QueryResult() {
    for (auto &entity : entities) {
      query_results_.push_back(std::move(entity));
    }
  }

  inline EntityPtrList &get_query_results() {
    return query_results_;
  }

  inline void add_query_result(EntityPtr &&entity) {
    query_results_.push_back(std::move(entity));
  }

  inline bool is_empty() { return query_results_.empty(); }

  inline void clear() { query_results_.clear(); }

  void IntersectWith(QueryResult &other_result);

  inline void Sort() {
    std::sort(query_results_.begin(), query_results_.end(),
              [](EntityPtr const &LHS, EntityPtr const &RHS) {
                return *LHS < *RHS;
              });
  }

 private:
  EntityPtrList query_results_;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;
}  // namespace qps
