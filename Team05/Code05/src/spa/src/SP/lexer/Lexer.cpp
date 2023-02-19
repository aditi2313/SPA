#include "Lexer.h"

#include <optional>
#include <stack>

#include "common/exceptions/SP.h"

namespace sp {
void Lexer::Increment() {
  std::optional<Token> token = std::nullopt;
  for (auto& handler_ptr : handlers) {
    if (token) {
      break;
    }
    token = handler_ptr->Handle(data_);
  }
  if (!token) {
    throw LexerException("No valid token found");
  }
  data_.set_current_token(token.value());
}

bool Lexer::IsDoubleCond() {
  std::stack<short> brackets;
  auto t_data = data_;
  bool result = false;
  // first token must be an open bracket
  if (get_tok() != Token::kTokOpenBracket) {
    return false;
  }
  while (!data_.is_end() && get_tok() != Token::kTokSemicolon) {
    if (get_tok() == Token::kTokOpenBracket) {
      brackets.push(1);
    }
    if (get_tok() == Token::kTokCloseBracket) {
      if (brackets.empty()) {
        // end of scope
        data_ = t_data;
        return result;
      }
      brackets.pop();
    }
    if (get_tok() == Token::kTokAnd || get_tok() == Token::kTokOr) {
      if (brackets.empty()) {
        result = true;
      }
    }
    Increment();
  }
  data_ = t_data;
  return result;
}
}  // namespace sp
