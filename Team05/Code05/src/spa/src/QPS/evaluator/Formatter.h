#pragma once

#include <set>
#include <string>
#include <vector>

#include "models/results/QueryResult.h"

namespace qps {
class Formatter {
 public:
  std::vector<std::string> FormatQuery(models::QueryResult query_result);
};
}  // namespace qps
