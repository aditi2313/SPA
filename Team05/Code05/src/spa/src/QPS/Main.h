#pragma once

#include <string>
#include <list>

namespace qps {
// Wrapper class for QPS
class Main {
 public:
  // Same function declaration as in TestWrapper
  void evaluate(std::string query, std::list<std::string> &results);
};
}  // namespace qps
