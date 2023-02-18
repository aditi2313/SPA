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

const std::unordered_set<Token>
    kKeyWordTokens{Token::kTokProcedure, Token::kTokRead,
                   Token::kTokPrint, Token::kTokCall,
                   Token::kTokWhile, Token::kTokIf,
                   Token::kTokThen, Token::kTokElse,
                   Token::kTokIdent};

const std::unordered_map<Token, std::string> kTokenToStringMap{
    {Token::kTokEof, "eof"},

    {Token::kTokProcedure, "procedure"},
    {Token::kTokRead, "read"},
    {Token::kTokPrint, "print"},
    {Token::kTokCall, "call"},
    {Token::kTokWhile, "while"},
    {Token::kTokIf, "if"},
    {Token::kTokElse, "else"},
    {Token::kTokThen, "then"},

    {Token::kTokIdent, "variable"},
    {Token::kTokInteger, "integer"},

    {Token::kTokOpenCurly, "{"},
    {Token::kTokCloseCurly, "}"},
    {Token::kTokSemicolon, ";"},
    {Token::kTokOpenBracket, "("},
    {Token::kTokCloseBracket, ")"},

    {Token::kTokEquals, "="},
    {Token::kTokPlus, "+"},
    {Token::kTokMinus, "-"},
    {Token::kTokTimes, "*"},
    {Token::kTokDiv, "/"},
    {Token::kTokMod, "%"},

    // relations
    {Token::kTokLess, "<"},
    {Token::kTokGreater, ">"},
    {Token::kTokGreaterEqual, ">="},
    {Token::kTokLessEqual, "<="},
    {Token::kTokEquiv, "=="},
    {Token::kTokNotEqual, "!="},

    // conditions
    {Token::kTokOr, "||"},
    {Token::kTokAnd, "&&"},
    {Token::kTokNot, "!"},

    // error
    {Token::kTokError, "error"},
};

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

std::string TokenToString(Token token) {
  return kTokenToStringMap.at(token);
}
}  // namespace sp
