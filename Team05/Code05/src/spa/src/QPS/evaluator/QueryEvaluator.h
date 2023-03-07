#pragma once

#include <memory>
#include <utility>
#include <set>

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class QueryEvaluator {
 public:
  explicit QueryEvaluator(pkb::PKBReadPtr &pkb)
      : pkb_(pkb) {}

  QueryResultPtr EvaluateQuery(
      QueryPtr &query);

 private:
  pkb::PKBReadPtr &pkb_;
  Table table_;
};
}  // namespace qps