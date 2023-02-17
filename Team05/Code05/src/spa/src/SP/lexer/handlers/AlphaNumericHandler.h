#pragma once

#include "LexerHandler.h"

namespace sp {
class AlphaNumericHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData& program) override;
};
}  // namespace sp
