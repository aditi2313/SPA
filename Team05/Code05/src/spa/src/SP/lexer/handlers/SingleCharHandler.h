#pragma once

#include <memory>

#include "LexerHandler.h"
#include "models/AST/Token.h"

namespace sp {
class SingleCharHandler : public LexerHandler {
 protected:
  std::optional<Token> Handle(LexerData& program) override;
};
}  // namespace sp
