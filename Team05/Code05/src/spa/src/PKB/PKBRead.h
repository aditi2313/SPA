#pragma once

#include <vector>
#include "models/results/ModifiesResult.h"
#include "common/filter/filters/ModifiesFilter.h"

namespace pkb {
class PKBRead {
 public:
  models::ModifiesResult Modifies(filter::ModifiesFilter);
};
}  // namespace pkb
