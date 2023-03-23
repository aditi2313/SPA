#pragma once

#include <set>
#include <string>
#include <vector>
#include <list>

#include "QPS/models/Entity.h"

namespace qps {
class Formatter {
 public:
  static std::list<std::string> FormatBooleanQuery(bool result);
  static std::list<std::string> FormatListQuery(
      std::vector<std::vector<Entity>> &results);
};
}  // namespace qps
