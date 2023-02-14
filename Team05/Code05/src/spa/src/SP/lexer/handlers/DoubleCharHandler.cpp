#include "DoubleCharHandler.h"

// all the double length tokens

const std::string kLessEqual = "<=";
const std::string kGreaterEqual = ">=";
const std::string kEqualTo = "==";
const std::string kNotEqual = "!=";

namespace sp {
std::optional<Token> DoubleCharHandler::Handle(LexerData& data) {
  LexerData temp_data = data;
  char c = data.get_current_char();
  data.increment_pointer();

  if (data.is_end()) return std::nullopt;
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
  data = temp_data;

  return std::nullopt;
}
}  // namespace sp
