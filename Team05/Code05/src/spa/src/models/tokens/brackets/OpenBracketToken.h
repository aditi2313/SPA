#pragma once

#include "Bracket.h"

namespace sp {
class OpenBracketToken : public Bracket {
 public:
  inline bool IsOpen() override { return true; }
};
}  // namespace sp