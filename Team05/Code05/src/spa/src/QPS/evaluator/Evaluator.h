#pragma once

#include <memory>
#include <utility>

#include "models/results/QueryResult.h"
#include "../models/Query.h"

namespace qps {
class Evaluator {
 public:
  models::QueryResult EvaluateQuery(Query query);

 private:
  std::unique_ptr<pkb::PKBRead> pkb;
};
}  // namespace qps
