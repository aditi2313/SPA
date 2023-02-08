#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <optional>
#include <unordered_map>

#include "models/AST/Token.h"

namespace sp {
class Lexer {
 public:
  explicit Lexer(std::string program);

  // returns the type of the next token
  int get_tok();

  /// <summary>
  /// Grabs the current word and
  /// figures out what it is.
  /// </summary>
  void Increment();

  /// <summary>
  /// Todo(Gab): switch from auto to whatever type we are sticking with. #40
  /// </summary>
  /// <returns></returns>
  inline auto GetTokAndIncrement() {
    auto tok = get_tok();
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

  // Define ptr to point towards the next token
  // On Increment, the pointer will point to one after the
  // Token
  int pointer_;

  // The enum representing the current token
  int current_tok_;

  // The word representing the current token (Only used for idents or read,
  // print, procedure, ...)
  std::string word_;

  // stores the integer which is reached
  int integer_;

  // Stores the statement count
  int stmt_ctr_ = 1;

  void ValidateInteger(std::string basicString);

  // TODO(Gab) Refactor this functionality with #40
  // something that is more specific
  // takes in a reference where the final pointer will be referenced.
  std::optional<Token> ReadRelation(int& p);

};
}  // namespace sp
