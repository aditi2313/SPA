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
  QueryEvaluator()
      : master_entity_factory_(std::make_unique<MasterEntityFactory>()) {}

  QueryResultPtr EvaluateQuery(
      QueryPtr &query,
      std::unique_ptr<pkb::PKBRead> &pkb);

 private:
  void InitializeSynonyms(
      QueryPtr &query,
      std::unique_ptr<pkb::PKBRead> &pkb);

  void InitializeEntitiesFromArgument(
      QueryPtr &query,
      ArgumentPtr &arg,
      std::unique_ptr<pkb::PKBRead> &pkb,
      EntityName entity_name,
      EntitySet &result);

  std::unique_ptr<MasterEntityFactory> master_entity_factory_;
};
}  // namespace qps
