#pragma once

#include <memory>
#include <utility>

#include "../models/Query.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  Evaluator() {
    master_entity_factory_ = std::make_unique<MasterEntityFactory>();
  }
  ListQueryResultPtr EvaluateQuery(std::unique_ptr<Query> &query);

  // Helper method for writing integration tests
  // where we set up our own PKB
  void inject_pkb(std::unique_ptr<pkb::PKBRead> &pkb) { pkb_ = std::move(pkb); }

  inline auto retrieve_pkb() { return std::move(pkb_); }

 private:
  std::unique_ptr<pkb::PKBRead> pkb_;
  std::unique_ptr<MasterEntityFactory> master_entity_factory_;
};
}  // namespace qps
