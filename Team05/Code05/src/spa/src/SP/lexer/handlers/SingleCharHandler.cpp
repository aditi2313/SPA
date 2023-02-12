#include "SingleCharHandler.h"

#include "models/AST/Token.h"

namespace sp {
std::optional<Token> SingleCharHandler::HandleInner(int& ptr,
                                                    std::string& program) {
  char c = program[ptr++];
  switch (c) {
    case '{':
      return {Token::kTokOpenCurly};
    case '}':
      return {Token::kTokCloseCurly};
    case ';':
      return {Token::kTokSemicolon};
    case '=':
      return {Token::kTokEquals};
    case '+':
      return {Token::kTokPlus};
    case '-':
      return {Token::kTokMinus};
    case '*':
      return {Token::kTokTimes};
    case '/':
      return {Token::kTokDiv};
    case '%':
      return {Token::kTokMod};
    case '(':
      return {Token::kTokOpenBracket};
    case ')':
      return {Token::kTokCloseBracket};
    case '!':
      return {Token::kTokNot};
    case '<':
      return {Token::kTokLess};
    case '>':
      return {Token::kTokGreater};
    default:
      ptr--;
      return std::nullopt;
  }
}

}  // namespace sp