#pragma once

#include "Filter.h"
#include "PKB/rows/Modifies.h"
#include "common/Exceptions.h"
#include <vector>


namespace filter {

class ModifiesFilter : public Filter<pkb::Modifies> {
 public:
  ModifiesFilter() {}
  std::vector<pkb::Modifies> filter(std::vector<pkb::Modifies>& modifies) {
    throw new NotImplementedException();
  }
 private:
  
};

}  // namespace filter
