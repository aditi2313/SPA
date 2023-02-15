#include "Token.h"

#include <vector>

namespace sp {
const std::vector<Token> kStmtTokens{Token::kTokRead, Token::kTokPrint,
                                     Token::kTokCall, Token::kTokWhile,
                                     Token::kTokIf};
bool IsStmtToken(Token input) {
  for (const auto& token : kStmtTokens) {
    if (token == input) {
      return true;
    }
  }
  return false;
}
}  // namespace sp
