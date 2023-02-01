#pragma once

#include <string>
#include <vector>

namespace pkb {

class Modifies {
 public:
  int getLine() { return line_; }
  std::vector<std::string> getVariables() { return variables_; }

 private:
  // the line that modifies
  int line_;

  // the name of the variables that this line modifies
  std::vector<std::string> variables_;
};

}  // namespace pkb
