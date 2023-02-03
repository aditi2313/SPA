#pragma once

#include <memory>
#include <set>
#include <utility>

#include "models/Entity.h"

// TODO(Gabau) Update Query Result wrapper for PKB
typedef std::shared_ptr<models::Entity> EntPtr;
struct cmp {
  bool operator()(const EntPtr& e1, const EntPtr& e2) const {
    return *e1 < *e2;
  }
};
typedef std::set<EntPtr, cmp> EntSet;

namespace models {

class QueryResult {
 public:
  QueryResult() {}
  inline EntSet& get_query_results() { return query_results_; }
  inline bool is_empty() { return query_results_.empty(); }
  inline void add_query_result(const EntPtr& entity) {
    query_results_.insert(entity);
  }

  void IntersectWith(QueryResult other_result);

 private:
  EntSet query_results_;
};
}  // namespace models
