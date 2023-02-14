#pragma once

#include <memory>
#include <optional>

#include "models/AST/Token.h"
#include "SP/lexer/LexerData.h"

namespace sp {
class LexerHandler {
 public:
  /*virtual std::optional<Token> Handle(int& ptr, std::string& program) {
    if (!next_handler_) {
      return std::nullopt;
    }
    auto current = HandleInner(ptr, program);
    if (!current) return next_handler_->Handle(ptr, program);
    return current;
  }*/

  virtual std::optional<Token> Handle(LexerData&) = 0;
};
}  // namespace sp
