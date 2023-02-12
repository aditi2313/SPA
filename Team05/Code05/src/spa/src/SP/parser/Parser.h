#pragma once

#include <memory>

#include "SP/lexer/Lexer.h"

namespace sp {
template <typename T>
class Parser {
 public:
  virtual std::unique_ptr<T> parse(Lexer&) = 0;
};

}  // namespace sp
