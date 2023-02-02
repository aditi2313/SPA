#pragma once

#include <set>

#include "models/EntityStub.h"

namespace qps {
class QueryResult {
 public:
  inline std::set<models::EntityStub> &get_query_results() {
    return query_results_;
  }
  inline bool is_empty() {
    return query_results_.empty();
  }
  inline void add_query_result(models::EntityStub entity) {
    query_results_.insert(entity);
  }

  void IntersectWith(QueryResult other_result);
 private:
  std::set<models::EntityStub> query_results_;
};
}  // namespace qps

