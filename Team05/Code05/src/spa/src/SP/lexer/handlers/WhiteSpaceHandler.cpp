#include "WhiteSpaceHandler.h"

namespace sp {
std::optional<Token> WhiteSpaceHandler::Handle(LexerData& data) {
  // iterate through the white space
  char c;
  while (isspace(c = data.get_current_char())) {
    data.increment_pointer();
  }
  return std::nullopt;
}
}  // namespace sp
