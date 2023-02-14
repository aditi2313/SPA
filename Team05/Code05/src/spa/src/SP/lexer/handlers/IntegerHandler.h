#pragma once

#include <optional>

#include "LexerHandler.h"
#include "SP/lexer/LexerData.h"

namespace sp {
class IntegerHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData& data) override;
};

}  // namespace sp
