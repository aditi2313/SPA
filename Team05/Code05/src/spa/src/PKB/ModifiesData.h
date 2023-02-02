#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace pkb {
class ModifiesData {
 public:
  int line_;
  std::vector<std::string> variables_;
};
}  // namespace pkb
