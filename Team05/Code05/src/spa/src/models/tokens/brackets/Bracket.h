#pragma once

#include "models/AST/tokens/Token.h"

namespace sp {

class Bracket : public Token {
 public:
  inline bool IsBracket() { return true; }
  virtual bool IsOpen() = 0;
};

}  // namespace sp