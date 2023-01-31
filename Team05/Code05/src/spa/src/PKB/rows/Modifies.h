#pragma once

#include <string>
#include <vector>


namespace pkb {

	
class Modifies {
 public:
  int getLine() { return line; }
  std::vector<std::string> getVariables() { return variables; }

 private:
  // the line that modifies
  int line;
  
  // the name of the variables that this line modifies
  std::vector<std::string> variables;
    
};


}
