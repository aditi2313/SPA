#pragma once

#include <algorithm>
#include <set>
#include <vector>
#include <utility>
#include <memory>

#include "Entity.h"
#include "QPS/evaluator/EntityFactory.h"

namespace qps {
class QueryResult {
 public:
  QueryResult() {}

  explicit QueryResult(EntitySet &entities) : QueryResult() {
    query_results_ = entities;
  }

  inline EntitySet &get_query_results() {
    return query_results_;
  }

  inline void add_query_result(Entity entity) {
    query_results_.insert(entity);
  }

  inline std::vector<Entity> Sort() {
    std::vector<Entity> arr(
        query_results_.begin(), query_results_.end());
    std::sort(arr.begin(), arr.end());
    return arr;
  }

  inline bool is_empty() { return query_results_.empty(); }

  inline void clear() { query_results_.clear(); }

 private:
  EntitySet query_results_;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;
}  // namespace qps
