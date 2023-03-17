#pragma once

#include <vector>

#include "QPS/models/Query.h"

namespace qps {
class ClauseOptimiser {
 public:
  using AdjList = std::vector<std::vector<int>>;

  std::vector<int> GroupClauses(std::vector<ClausePtr> &clauses);

 private:
  AdjList &PreprocessClauses(std::vector<ClausePtr> &clauses);
};
}  // namespace qps
