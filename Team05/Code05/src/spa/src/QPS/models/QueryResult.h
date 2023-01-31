#pragma once

#include <vector>

#include "models/EntityStub.h"

namespace qps {
class QueryResult {
 private:
  std::vector<models::EntityStub> query_results_;
 public:
  std::vector<models::EntityStub> GetQueryResults() {
    return query_results_;
  }
};
}

