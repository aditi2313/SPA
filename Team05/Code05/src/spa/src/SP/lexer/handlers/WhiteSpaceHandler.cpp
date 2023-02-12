#include "WhiteSpaceHandler.h"

namespace sp {
std::optional<Token> WhiteSpaceHandler::HandleInner(int& ptr,
                                                    std::string& program) {
  // iterate through the white space
  char c = program[ptr];
  while (isspace(c = program[ptr])) {
    ptr++;
  }
  return std::nullopt;
}
}  // namespace sp