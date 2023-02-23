#pragma once

#include <memory>
#include <utility>
#include <set>

#include "../models/Query.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  explicit Evaluator()
      : master_entity_factory_(std::make_unique<MasterEntityFactory>()) {}

  QueryResultPtr EvaluateQuery(
      QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb);

 private:
  void InitializeSynonyms(QueryPtr &query, std::unique_ptr<pkb::PKBRead> &pkb);
  void InitializeEntitiesFromArgument(
      QueryPtr &query, ArgumentPtr &arg, std::unique_ptr<pkb::PKBRead> &pkb,
      EntityName entity_name, EntityPtrList &result);

  void UpdateSynonymEntityList(
      QueryPtr &query, ArgumentPtr &arg,
      EntityPtrHashset const &result);
  bool EvaluateClause(QueryPtr &query, ClausePtr &clause, std::unique_ptr<pkb::PKBRead> &pkb);

  std::unique_ptr<MasterEntityFactory> master_entity_factory_;
};
}  // namespace qps
