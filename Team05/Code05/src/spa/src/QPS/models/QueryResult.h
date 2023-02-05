#pragma once

#include <set>

#include "models/Entity.h"
#include "QPS/evaluator/EntityFactory.h"

namespace qps {
class QueryResult {
 public:
  QueryResult() {}
  QueryResult(EntityPtrList &entities) {
    for (auto &entity : entities) {
      query_results_.push_back(std::move(entity));
    }
  }
  inline std::vector<models::EntityPtr> &get_query_results() {
    return query_results_;
  }
  inline void add_query_result(EntityPtr &entity) {
    query_results_.push_back(std::move(entity));
  }
  inline bool is_empty() { return query_results_.empty(); }

  void IntersectWith(QueryResult other_result);

 private:
  EntityPtrList query_results_;
};

using QueryResultPtr = std::unique_ptr<QueryResult>;

}  // namespace qps
