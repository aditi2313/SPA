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

  /// <summary>
  /// Todo(Gab): switch from auto to whatever type we are sticking with.
  /// </summary>
  /// <returns></returns>
  inline auto GetTokAndIncrement() {
    auto tok = GetTok();
    return tok;
  }
  // returns the type of the next token
  int GetTok();

  // Todo(Gab): refactor code to do the following
  ///
  /// Move the lexer to the next token.
  ///
  void Increment();

  inline std::string get_ident() const { return ident_; }
  inline int get_integer() const { return integer_; }

  inline int get_and_increment_stmtctr() { return stmt_ctr_++; }

  // Todo(Gab) decide on how to implement Tokens
  // bool IsCurrentTokenAdd();

  //// TODO(Gab) refactor code from GetNext into this.
  // bool IsCurrentTokenIdent();
  // bool IsCurrentTokenEof();
  // bool IsCurrentTokenRead();
  // bool IsCurrentTokenCall();
  // bool IsCurrentTokenWhile();
  // bool IsCurrentTokenIf();
  // bool IsCurrentTokenInt();
  // bool IsCurrentTokenOpenCurly();
  // bool IsCurrentTokenCloseCurly();
  // bool IsCurrentTokenSemiColon();
  // bool IsCurrentTokenEquals();
  // bool IsCurrentTokenPlus();
  // bool IsCurrentTokenMinus();
  // bool IsCurrentTokenTimes();
  // bool IsCurrentTokenDiv();
  // bool IsCurrentTokenMod();

 private:
  std::string program_;
  int pointer_;
  int current_char_;

  std::string ident_;
  int integer_;
  int stmt_ctr_;
  void ValidateInteger(std::string basicString);
};
}  // namespace sp
