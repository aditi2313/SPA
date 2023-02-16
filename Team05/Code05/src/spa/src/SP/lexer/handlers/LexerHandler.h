#pragma once

#include <memory>
#include <optional>

#include "SP/lexer/LexerData.h"
#include "models/AST/Token.h"

namespace sp {

/// <summary>
/// An implmentation of
/// the strategy design pattern,
/// abstracting out the different strategies used
/// to extract tokens into their own classes.
/// </summary>
class LexerHandler {
 public:
  /// <summary>
  /// Method used to by the handler to manipulate
  /// the data within the Lexer.
  /// </summary>
  /// <param name="data">The object representing the data contained within the
  /// lexer.</param> <returns></returns>
  virtual std::optional<Token> Handle(LexerData&) = 0;
};
}  // namespace sp
