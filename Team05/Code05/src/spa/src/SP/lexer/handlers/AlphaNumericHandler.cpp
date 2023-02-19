#include "AlphaNumericHandler.h"

#include <string>

#include "models/AST/Token.h"

namespace sp {
std::optional<Token> AlphaNumericHandler::Handle(LexerData &data) {
  char c = data.get_current_char();
  // NAME: LETTER (LETTER | DIGIT)*
  if (!isalpha(c)) {
    return std::nullopt;
  }
  std::string word;
  word = c;
  data.increment_pointer();
  while (!data.is_end() && isalnum(c = data.get_current_char())) {
    word += c;
    data.increment_pointer();
  }
  data.set_word(word);
  if (IsTokenString(word)) {
    return StringToToken(word);
  }
  return {Token::kTokIdent};
}
}  // namespace sp
