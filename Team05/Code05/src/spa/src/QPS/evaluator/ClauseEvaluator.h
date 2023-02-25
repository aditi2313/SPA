#pragma once

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"

namespace qps {
class ClauseEvaluator {
 public:
  static bool EvaluateClause(
      QueryPtr &query,
      ClausePtr &clause,
      Table &clause_table,
      std::unique_ptr<pkb::PKBRead> &pkb);
};
}  // namespace qps
