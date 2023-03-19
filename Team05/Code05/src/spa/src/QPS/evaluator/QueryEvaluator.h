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
  bool EvaluateClause(ClausePtr &clause);
  QueryResultPtr BuildResult(QueryPtr &query);

  pkb::PKBReadPtr &pkb_;
  Table table_;
  ClauseEvaluator clause_evaluator_;

  bool has_table_been_intialized_ = false;
};
}  // namespace qps
