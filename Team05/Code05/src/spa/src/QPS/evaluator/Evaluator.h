#pragma once

#include <memory>
#include <utility>

#include "../models/QueryResult.h"
#include "../models/Query.h"

namespace qps {
class Evaluator {
 public:
  QueryResult EvaluateQuery(Query query);

 private:
  std::unique_ptr<pkb::PKBStub> pkb;
};
}  // namespace qps
