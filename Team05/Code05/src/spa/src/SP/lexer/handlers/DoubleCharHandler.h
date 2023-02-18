#pragma once
#include "LexerHandler.h"

namespace sp {
class DoubleCharHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData& program) override;
};
}  // namespace sp
