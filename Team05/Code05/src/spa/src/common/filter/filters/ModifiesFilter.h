#pragma once

#include "Filter.h"
#include "PKB/rows/Modifies.h"
#include <vector>

namespace filter {

class ModifiesFilter : public Filter<Modifies> {
 public:
  ModifiesFilter() {}
  
 private:

};

}  // namespace filter
