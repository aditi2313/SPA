#pragma once

#include "models/tokens/Token.h"

namespace sp {
  class StmtToken : public Token {
 public:
    inline bool IsStmt() override { return true; }
  };
}
