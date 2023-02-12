#pragma once

#include "models/tokens/Token.h"

namespace sp {
class LogicalToken : public Token {
 public:
  inline bool IsLogical override { return true; }
};
}  // namespace sp