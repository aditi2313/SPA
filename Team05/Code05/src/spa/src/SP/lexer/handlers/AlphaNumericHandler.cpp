#include "AlphaNumericHandler.h"

#include <string>

namespace sp {
std::optional<Token> AlphaNumericHandler::Handle(LexerData& data) {
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
  if (word == "procedure") {
    return {Token::kTokProcedure};
  }
  if (word == "read") {
    return {Token::kTokRead};
  }
  if (word == "print") {
    return {Token::kTokPrint};
  }
  if (word == "call") {
    return {Token::kTokCall};
  }
  if (word == "while") {
    return {Token::kTokWhile};
  }
  if (word == "if") {
    return {Token::kTokIf};
  }
  return {Token::kTokIdent};
}
}  // namespace sp
