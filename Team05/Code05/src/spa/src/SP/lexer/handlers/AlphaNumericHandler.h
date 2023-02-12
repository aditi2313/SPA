#pragma once

#include "LexerHandler.h"

namespace sp {
  class AlphaNumericHandler : public LexerHandler {
  protected:
    std::optional<Token> HandleInner(int& ptr, std::string& program);
  };
}