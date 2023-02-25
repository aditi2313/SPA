#pragma once

#include <memory>
#include <utility>
#include <set>

#include "QPS/models/Query.h"
#include "QPS/models/Table.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class QueryEvaluator {
 public:
  explicit QueryEvaluator(pkb::PKBPtr &pkb)
      : pkb_(pkb),
        master_entity_factory_(std::make_unique<MasterEntityFactory>(pkb)) {}

  QueryResultPtr EvaluateQuery(
      QueryPtr &query);

 private:
  void InitializeEntitiesFromArgument(
      ArgumentPtr &arg,
      EntityName entity_name,
      EntitySet &result);

  pkb::PKBPtr &pkb_;
  std::unique_ptr<MasterEntityFactory> master_entity_factory_;
  Table table_;
};
}  // namespace qps
