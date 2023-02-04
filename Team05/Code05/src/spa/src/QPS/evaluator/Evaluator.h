#pragma once

#include <memory>
#include <utility>

#include "../models/Query.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  QueryResult EvaluateQuery(Query query);

 private:
  std::unique_ptr<pkb::PKBRead> pkb;
};
}  // namespace qps
