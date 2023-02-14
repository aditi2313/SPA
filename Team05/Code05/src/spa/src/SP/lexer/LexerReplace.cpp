#include "LexerReplace.h"

#include <optional>

#include "common/exceptions/SP.h"

namespace sp {
void Lexer::Increment() {
  std::optional<Token> token = std::nullopt;
  for (auto& handler_ptr : handlers) {
    if (token) {
      break;
    }
    token = handler_ptr->Handle(data_);
  }
  if (!token) {
    throw LexerException("No valid token found");
  }
  current_token_ = token.value();
}
}  // namespace sp