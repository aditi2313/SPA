#pragma once

#include "Bracket.h"
namespace sp {

class ClosedBracketToken : public Bracket {
 public:
  inline bool IsOpen() override { return false; }
};
}  // namespace sp
