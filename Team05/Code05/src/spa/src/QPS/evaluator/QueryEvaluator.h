#pragma once

#include <memory>
#include <utility>
#include <set>

#include "ClauseEvaluator.h"
#include "QPS/models/Query.h"
#include "QPS/models/Table.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class QueryEvaluator {
 public:
  explicit QueryEvaluator(pkb::PKBReadPtr &pkb)
      : pkb_(pkb), clause_evaluator_(ClauseEvaluator(pkb_)) {}

  QueryResultPtr EvaluateQuery(
      QueryPtr &query);

 private:
  void UpdateTableWithElem(QueryPtr &query, Elem elem);
  bool EvaluateClause(ClausePtr &clause, Table &group_table);
  QueryResultPtr BuildResult(QueryPtr &query);

  pkb::PKBReadPtr &pkb_;
  Table query_table_;
  ClauseEvaluator clause_evaluator_;
};
}  // namespace qps
