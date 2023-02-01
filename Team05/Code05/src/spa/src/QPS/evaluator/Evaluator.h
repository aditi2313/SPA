#pragma once

#include "../models/QueryResult.h"
#include "../models/Query.h"

namespace qps {
class Evaluator {
 public:
  QueryResult EvaluateQuery(Query query);
};
}  // namespace qps
