#pragma once

#include <string>

#include "../models/QueryResult.h"

namespace qps {
class Formatter {
 public:
  std::vector<std::string> FormatQuery(QueryResult query_result);
};
}  // namespace qps
