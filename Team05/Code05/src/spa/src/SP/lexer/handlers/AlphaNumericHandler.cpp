#include "AlphaNumericHandler.h"

#include <string>

const char kProcedure[] = "procedure";
const char kRead[] = "read";
const char kPrint[] = "print";
const char kWhile[] = "while";
const char kCall[] = "call";
const char kIf[] = "if";
const char kElse[] = "else";
const char kThen[] = "then";

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
  if (word == kProcedure) {
    return {Token::kTokProcedure};
  }
  if (word == kRead) {
    return {Token::kTokRead};
  }
  if (word == kPrint) {
    return {Token::kTokPrint};
  }
  if (word == kCall) {
    return {Token::kTokCall};
  }
  if (word == kWhile) {
    return {Token::kTokWhile};
  }
  if (word == kIf) {
    return {Token::kTokIf};
  }
  if (word == kElse) {
    return {Token::kTokElse};
  }
  if (word == kThen) {
    return {Token::kTokThen};
  }
  return {Token::kTokIdent};
}
}  // namespace sp
