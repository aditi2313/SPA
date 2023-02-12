#pragma once

#include <set>
#include <string>
#include <list>

#include "QPS/models/QueryResult.h"

namespace qps {
class Formatter {
 public:
  std::list<std::string> FormatQuery(ListQueryResultPtr &query_result);
};
}  // namespace qps
