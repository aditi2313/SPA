#pragma once

#include <set>

#include "models/EntityStub.h"

namespace qps {
class QueryResult {
 private:
  std::set<models::EntityStub> query_results_;
 public:
  std::set<models::EntityStub> GetQueryResults() {
    return query_results_;
  }
  bool IsEmpty() {
    return query_results_.empty();
  }

  void AddQueryResult(models::EntityStub entity) {
    query_results_.insert(entity);
  }

  void Intersect(QueryResult other_result);
};
}

