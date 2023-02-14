#include "SingleCharHandler.h"

#include "models/AST/Token.h"

namespace sp {
std::optional<Token> SingleCharHandler::Handle(LexerData& data) {
  char c = data.get_current_char();
  data.increment_pointer();
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
      data.decrement_pointer();
      return std::nullopt;
  }
}

}  // namespace sp
