#pragma once

#include <memory>
#include <utility>
#include <set>

#include "../models/Query.h"
#include "QPS/models/QueryResult.h"

namespace qps {
class Evaluator {
 public:
  explicit Evaluator(std::unique_ptr<pkb::PKBRead> &pkb) {
    master_entity_factory_ = std::make_unique<MasterEntityFactory>();
    pkb_ = std::move(pkb);
  }

  void InitializeSynonyms(QueryPtr &query);
  void InitializeEntitiesFromArgument(
      QueryPtr &query, ArgumentPtr &arg,
      EntityName entity_name, EntityPtrList &result);

  void UpdateSynonymEntityList(
      QueryPtr &query, ArgumentPtr &arg, std::set<EntityPtr> &result);

  QueryResultPtr EvaluateQuery(QueryPtr &query);
  bool EvaluateClause(QueryPtr &query, ClausePtr &clause);

  inline auto retrieve_pkb() { return std::move(pkb_); }

 private:
  std::unique_ptr<pkb::PKBRead> pkb_;
  std::unique_ptr<MasterEntityFactory> master_entity_factory_;
};
}  // namespace qps
