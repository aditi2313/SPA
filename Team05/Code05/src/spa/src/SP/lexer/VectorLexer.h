#pragma once

#include <stack>
#include <string>
#include <vector>

#include "Lexer.h"
namespace sp {
/// <summary>
/// VectorLexer wraps around lexer
/// to provide reverse navigation, within brackets, semicolons and relations.
/// For instance, (a + x < a - b), If the pointer is on the first bracket,
/// we will take "(a + x" as the string that this lexer will provide, with the
/// pointer pointing at the end of aforementioned string.
/// </summary>
class VectorLexer {
 public:
  /// <summary>
  /// Consumes the tokens in the given lxr until
  /// the end of the lexer and constructs a
  /// reverse lexer for that particular
  /// sequence of tokens.
  /// </summary>
  /// <param name="lxr"></param>
  explicit VectorLexer(Lexer& lxr) {
    std::stack<int> brackets;
    while (lxr.get_tok() != Token::kTokSemicolon &&
           lxr.get_tok() != Token::kTokEof && !IsRelationToken(lxr.get_tok())) {
      if (lxr.get_tok() == Token::kTokOpenBracket) {
        brackets.push(1);
      }
      if (lxr.get_tok() == Token::kTokCloseBracket) {
        if (brackets.empty()) break;
        brackets.pop();
      }
      tokens_.push_back(lxr.get_tok());
      if (!IsStmtToken(lxr.get_tok())) {
        // reduce space used
        idents_.push_back("");
      } else {
        idents_.push_back(lxr.get_ident());
      }

      numbers_.push_back(lxr.get_integer());
      lxr.Increment();
    }
    ptr_ = tokens_.size() - 1;
  }

  Token get_tok() {
    if (IsEnd()) {
      return Token::kTokEof;
    }
    return tokens_[ptr_];
  }
  std::string get_ident() { return idents_[ptr_]; }
  int get_integer() { return numbers_[ptr_]; }
  inline void Decrement() { ptr_--; }
  inline void Increment() { ptr_++; }
  inline bool IsEnd() { return ptr_ < 0 || ptr_ >= tokens_.size(); }

 private:
  std::vector<Token> tokens_;
  std::vector<std::string> idents_;
  std::vector<int> numbers_;
  int ptr_;
};
}  // namespace sp
