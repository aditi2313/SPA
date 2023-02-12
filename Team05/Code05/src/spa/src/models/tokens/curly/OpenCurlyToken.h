#pragma once

#include "CurlyToken.h"

namespace sp {
class OpenCurlyToken : public CurlyToken {
 public:
  inline bool IsOpen() override { return true; }
};
}  // namespace sp