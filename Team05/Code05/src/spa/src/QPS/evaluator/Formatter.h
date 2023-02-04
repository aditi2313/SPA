#pragma once

#include <set>
#include <string>
#include <vector>

#include "QPS/models/QueryResult.h"

namespace qps {
class Formatter {
 public:
  std::vector<std::string> FormatQuery(QueryResult query_result);
};
}  // namespace qps
