#include "DoubleCharHandler.h"

// all the double length tokens

const std::string kLessEqual = "<=";
const std::string kGreaterEqual = ">=";
const std::string kEqualTo = "==";
const std::string kNotEqual = "!=";

namespace sp {
std::optional<Token> DoubleCharHandler::HandleInner(int& ptr,
                                                    std::string& program) {
  if (ptr + 1 >= program.length()) return std::nullopt;
  std::string word = std::string() + program[ptr] + program[ptr + 1];
  ptr += 2;
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
  return std::nullopt;
}
}  // namespace sp