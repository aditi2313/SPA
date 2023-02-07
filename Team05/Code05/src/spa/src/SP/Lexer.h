#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "models/AST/Token.h"

namespace sp {
class Lexer {
 public:
  explicit Lexer(std::string program);

  // returns the type of the next token
  int GetTok();

  /// <summary>
  /// Grabs the current word and
  /// figures out what it is.
  /// </summary>
  void Increment();

  /// <summary>
  /// Todo(Gab): switch from auto to whatever type we are sticking with.
  /// </summary>
  /// <returns></returns>
  inline auto GetTokAndIncrement() {
    auto tok = GetTok();
    Increment();
    return tok;
  }

  inline std::string get_ident() const { return word_; }
  inline int get_integer() const { return integer_; }

  inline int GetAndIncrementStmtCtr() { return stmt_ctr_++; }

 private:
  std::string program_;

  /// <summary>
  /// Reads a word into word_.
  /// Returns false if the next token
  /// is not a valid word.
  /// </summary>
  /// <returns></returns>
  bool ReadWord();

  bool ReadInt();

  // Define ptr to point towards the current char
  int pointer_;
  int current_tok_;
  std::string word_;
  int integer_;
  int stmt_ctr_;
  void ValidateInteger(std::string basicString);
};
}  // namespace sp
