#pragma once

#include "LexerHandler.h"
#include "SP/lexer/LexerData.h"

namespace sp {
class ErrorHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData&) override;
};
}  // namespace sp
