#include "Token.h"

#include <unordered_set>
#include <vector>

namespace sp {
const std::vector<Token> kStmtTokens{Token::kTokRead, Token::kTokPrint,
                                     Token::kTokCall, Token::kTokWhile,
                                     Token::kTokIf,   Token::kTokIdent};

const std::unordered_set<Token> kRelationTokens{
    Token::kTokAnd,     Token::kTokOr,           Token::kTokLess,
    Token::kTokGreater, Token::kTokGreaterEqual, Token::kTokLessEqual,
    Token::kTokEquiv};
bool IsStmtToken(Token input) {
  for (const auto& token : kStmtTokens) {
    if (token == input) {
      return true;
    }
  }
  return false;
}

// Todo(Gab) replace with functionality from #80
bool IsKeyWordToken(Token token) { return token == Token::kTokIdent; }

bool IsRelationToken(Token token) { return kRelationTokens.count(token) == 1; }
}  // namespace sp
