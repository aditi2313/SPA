#include "WhiteSpaceHandler.h"

namespace sp {
std::optional<Token> WhiteSpaceHandler::Handle(LexerData& data) {
  // iterate through the white space
  char c;
  while (!data.is_end() && isspace(c = data.get_current_char())) {
    data.increment_pointer();
  }
  if (data.is_end()) {
    return Token::kTokEof;
  }
  return std::nullopt;
}
}  // namespace sp
