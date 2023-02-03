#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace pkb {
class ModifiesData {
 public:
  int line_;
  std::vector<std::string> variables_;
  ModifiesData(int line, std::vector<std::string> variables);
};
}  // namespace pkb
