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
                std::unique_ptr<pkb::PKBRead> &pkb);
};
}  // namespace qps
