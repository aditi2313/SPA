#pragma once

#include <vector>

#include "Filter.h"
#include "PKB/rows/Modifies.h"
#include "common/Exceptions.h"

namespace filter {

class ModifiesFilter : public Filter<pkb::Modifies> {
 public:
  ModifiesFilter() {}
  std::vector<pkb::Modifies> Filter(
      const std::vector<pkb::Modifies>& modifies) {
    throw new NotImplementedException();
  }

 private:
};

}  // namespace filter
