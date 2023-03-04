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
  virtual inline bool is_boolean() {
    return false;
  }
  virtual ~QueryResult() = default;
};

class BooleanQueryResult : public QueryResult {
 public:
  explicit BooleanQueryResult(bool is_true)
      : QueryResult(), is_true_(is_true) {}

  inline bool is_boolean() override {
    return true;
  }

  inline bool is_true() {
    return is_true_;
  }

 private:
  bool is_true_;
};

class ListQueryResult : public QueryResult {
 public:
  ListQueryResult() : QueryResult() {}

  explicit ListQueryResult(std::vector<std::vector<Entity>> &results)
      : QueryResult(), query_results_(results) {}

  std::vector<std::vector<Entity>> &get_query_results() {
    return query_results_;
  }

 private:
  std::vector<std::vector<Entity>> query_results_;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;
}  // namespace qps
