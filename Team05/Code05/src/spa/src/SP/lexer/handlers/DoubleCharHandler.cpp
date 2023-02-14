#include "DoubleCharHandler.h"

#include <string>

// all the double length tokens

const char kLessEqual[] = "<=";
const char kGreaterEqual[] = ">=";
const char kEqualTo[] = "==";
const char kNotEqual[] = "!=";
const char kAnd[] = "&&";
const char kOr[] = "||";

namespace sp {
std::optional<Token> DoubleCharHandler::Handle(LexerData& data) {
  LexerData temp_data = data;
  char c = data.get_current_char();
  data.increment_pointer();

  if (data.is_end()) {
    data = temp_data;
    return std::nullopt;
  }
  std::string word = std::string() + c + data.get_current_char();
  data.increment_pointer();

  if (word == kLessEqual) {
    return {Token::kTokLessEqual};
  }
  if (word == kGreaterEqual) {
    return {Token::kTokGreaterEqual};
  }
  if (word == kEqualTo) {
    return {Token::kTokEquiv};
  }
  if (word == kNotEqual) {
    return {Token::kTokNotEqual};
  }
  if (word == kAnd) {
    return {Token::kTokAnd};
  }
  if (word == kOr) {
    return {Token::kTokOr};
  }
  data = temp_data;

  return std::nullopt;
}
}  // namespace sp
