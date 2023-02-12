#pragma once

#include "models/tokens/Token.h"

namespace sp {
class ComparisonToken {
 public:
  inline bool IsComparison() override { return true; }
};
}  // namespace sp
