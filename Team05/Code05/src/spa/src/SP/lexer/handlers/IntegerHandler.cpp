#include "IntegerHandler.h"

#include "common/exceptions/SP.h"

namespace sp {

void ValidateInteger(std::string number_string) {
  if (number_string[0] == '0' && number_string.length() > 1) {
    throw LexerException("Integer cannot have leading zeroes");
  }

  for (int i = 0; i < number_string.length(); i++) {
    if (!isdigit(number_string[i])) {
      throw LexerException("Integer cannot have non-digits");
    }
  }
}
std::optional<Token> IntegerHandler::Handle(LexerData& data) {
  std::string result_int;
  char current_char = data.get_current_char();
  if (!isdigit(current_char)) {
    return std::nullopt;
  }

  // current token is an INTEGER
  // INTEGER : 0 | NZDIGIT ( DIGIT )*
  std::string number_string;
  while (!data.is_end() && !isspace(current_char) && current_char != ';') {
    number_string += current_char;
    data.increment_pointer();
    current_char = data.get_current_char();
  }

  ValidateInteger(number_string);
  data.set_int(std::stoi(number_string));
  return {Token::kTokInteger};
}
}  // namespace sp