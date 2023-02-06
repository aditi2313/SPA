#pragma once

#include <memory>

#include "Lexer.h"

namespace sp {
<typename T> class Parser {
 public:
  std::unique_ptr<T> parse(Lexer&) = 0;
};

}  // namespace sp
