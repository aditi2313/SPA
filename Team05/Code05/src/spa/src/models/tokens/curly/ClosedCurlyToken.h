#pragma once

#include "CurlyToken.h"

namespace sp {
class ClosedCurlyToken : public CurlyToken {
 public:
  inline bool IsOpen() override { return false; }
};
}  // namespace sp