#pragma once

#include <memory>
#include <utility>

#include "../models/Query.h"
#include "models/results/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  models::QueryResult EvaluateQuery(Query query);

 private:
  std::unique_ptr<pkb::PKBRead> pkb;
};
}  // namespace qps
