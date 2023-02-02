#pragma once

#include <vector>

#include "common/filter/filters/ModifiesFilter.h"
#include "models/results/ModifiesResult.h"

namespace pkb {
class PKBRead {
 public:
  models::ModifiesResult Modifies(filter::ModifiesFilter);
};
}  // namespace pkb
