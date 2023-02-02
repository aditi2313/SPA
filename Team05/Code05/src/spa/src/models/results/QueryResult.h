#pragma once

#include <memory>
#include <set>

#include "models/EntityStub.h"

// todo figure out why unique isn't working
typedef std::shared_ptr<models::EntityStub> EntPtr;
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
  inline void add_query_result(EntPtr& entity) {
    query_results_.insert(std::move(entity));
  }

  void IntersectWith(QueryResult other_result);

 private:
  EntSet query_results_;
};
}  // namespace models
