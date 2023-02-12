#pragma once

#include "models/tokens/Token.h"

namespace sp {
class CurlyToken : public Token {
 public:
  inline bool IsCurly() { return true; }
};
}  // namespace sp