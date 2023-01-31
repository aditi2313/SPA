#pragma once

#include <string>
#include <vector>
#include "common/filter/filters/ModifiesFilter.h"

namespace pkb {

	
class Modifies {
 public:
  int getLine() { return line; }
  std::vector<std::string> getVariables() { return variables; }

 private:
  // the line that modifies
  int line;
  friend class ModifiesFilter;
  // the name of the variables that this line modifies
  std::vector<std::string> variables;
};


}
