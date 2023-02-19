#include "SingleCharHandler.h"

#include <string>

#include "models/AST/Token.h"

namespace sp {
std::optional<Token> SingleCharHandler::Handle(LexerData &data) {
  char c = data.get_current_char();
  data.increment_pointer();
  std::string str = std::string(1, c);
  if (IsTokenString(str)) {
    return StringToToken(str);
  }
  data.decrement_pointer();
  return std::nullopt;
}
}  // namespace sp
