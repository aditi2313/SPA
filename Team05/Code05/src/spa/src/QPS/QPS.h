#pragma once

#include <string>
#include <list>

#include "PKB/PKBRead.h"

namespace qps {
// Wrapper class for QPS
class QPS {
 public:
  // Same function declaration as in TestWrapper
  void evaluate(std::string query, std::list<std::string> &results);

  // Overloaded function to use for integration tests
  // where we inject our own PKB
  void evaluate(std::string query, std::list<std::string> &results, std::unique_ptr<pkb::PKBRead> &pkb);

};
}  // namespace qps
