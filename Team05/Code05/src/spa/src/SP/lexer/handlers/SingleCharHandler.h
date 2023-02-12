#pragma once

#include <memory>

#include "LexerHandler.h"
#include "models/AST/Token.h"

namespace sp {
class SingleCharHandler : public LexerHandler {
 protected:
  std::optional<Token> HandleInner(int& ptr, std::string& program) override;
};
}  // namespace sp