#include "Token.h"

#include <unordered_set>
#include <vector>
#include <unordered_set>

namespace sp {
const std::vector<Token> kStmtTokens{Token::kTokRead, Token::kTokPrint,
                                     Token::kTokCall, Token::kTokWhile,
                                     Token::kTokIf,   Token::kTokIdent};

const std::unordered_set<Token> kRelationTokens{
    Token::kTokAnd,     Token::kTokOr,           Token::kTokLess,
    Token::kTokGreater, Token::kTokGreaterEqual, Token::kTokLessEqual,
    Token::kTokEquiv};

const std::unordered_set<Token>
    kKeyWordTokens{Token::kTokProcedure, Token::kTokRead,
                   Token::kTokPrint, Token::kTokCall,
                   Token::kTokWhile, Token::kTokIf,
                   Token::kTokThen, Token::kTokElse,
                   Token::kTokIdent};

bool IsStmtToken(Token input) {
  for (const auto& token : kStmtTokens) {
    if (token == input) {
      return true;
    }
  }
  return false;
}

bool IsKeyWordToken(Token token) { return kKeyWordTokens.count(token) == 1; }

bool IsRelationToken(Token token) { return kRelationTokens.count(token) == 1; }
}  // namespace sp
