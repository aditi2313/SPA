#pragma once

#include <list>
#include <memory>
#include <string>

#include "PKB/PKBRead.h"

namespace qps {
// Wrapper class for QPS
class QPS {
 public:
  void evaluate(std::string query,
                std::list<std::string> &results,
                pkb::PKBReadPtr &pkb);
};
}  // namespace qps
