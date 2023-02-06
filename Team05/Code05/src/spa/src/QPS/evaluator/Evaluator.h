#pragma once

#include <memory>
#include <utility>

#include "../models/Query.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  QueryResult EvaluateQuery(std::unique_ptr<Query> query);

  // Helper method for writing integration tests
  // where we set up our own PKB
  void inject_pkb(std::unique_ptr<pkb::PKBRead> &pkb) {
    pkb_ = std::move(pkb);
  }

  auto retrieve_pkb() { return std::move(pkb_);
  }

 private:  
  std::unique_ptr<pkb::PKBRead> pkb_;
};
}  // namespace qps
