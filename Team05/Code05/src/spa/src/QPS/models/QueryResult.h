#pragma once

#include <algorithm>
#include <set>
#include <vector>
#include <utility>
#include <list>
#include <string>
#include <memory>

#include "Entity.h"
#include "QPS/evaluator/Formatter.h"

namespace qps {
class QueryResult {
 public:
  virtual void Format(
      std::list<std::string> &results) = 0;

  virtual ~QueryResult() = default;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;

class BooleanQueryResult : public QueryResult {
 public:
  explicit BooleanQueryResult(bool result)
      : QueryResult(), result_(result) {}

  inline static QueryResultPtr BuildFalse() {
    return std::make_unique<BooleanQueryResult>(false);
  }

  inline void Format(
      std::list<std::string> &results) override {
    results = Formatter::FormatBooleanQuery(result_);
  }

 private:
  bool result_;
};

class ListQueryResult : public QueryResult {
 public:
  ListQueryResult() : QueryResult() {}

  explicit ListQueryResult(std::vector<std::vector<Entity>> &results)
      : QueryResult(), query_results_(results) {}

  inline static QueryResultPtr BuildEmpty() {
    return std::make_unique<ListQueryResult>();
  }

  std::vector<std::vector<Entity>> &get_query_results() {
    return query_results_;
  }

  inline void Format(
      std::list<std::string> &results) override {
    results = Formatter::FormatListQuery(query_results_);
  }

 private:
  std::vector<std::vector<Entity>> query_results_;
};

}  // namespace qps
