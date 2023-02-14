#pragma once

#include "AlphaNumericHandler.h"
#include "LexerHandler.h"

namespace sp {
class WhiteSpaceHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData&) override;
};
}  // namespace sp
