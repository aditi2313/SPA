#include "DoubleCharHandler.h"

#include <string>

// all the double length tokens

namespace sp {
std::optional<Token> DoubleCharHandler::Handle(LexerData &data) {
  LexerData temp_data = data;
  char c = data.get_current_char();
  data.increment_pointer();

  if (data.is_end()) {
    data = temp_data;
    return std::nullopt;
  }
  std::string word = std::string() + c + data.get_current_char();
  data.increment_pointer();

  if (IsTokenString(word)) {
    return StringToToken(word);
  }

  data = temp_data;
  return std::nullopt;
}
}  // namespace sp
