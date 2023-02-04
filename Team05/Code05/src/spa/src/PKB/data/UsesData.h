#pragma once
#include <string>
#include <vector>

namespace pkb {

class UsesData {
  UsesData(int line, std::vector<std::string> variable_names)
      : line_(line), variable_names_(variable_names) {}

 public:
  int line_;
  std::vector<std::string> variable_names_;
};
}  // namespace pkb