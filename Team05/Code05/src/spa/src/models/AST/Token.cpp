#include "Token.h"

#include <unordered_set>
#include <vector>

namespace sp {
const std::unordered_set<Token> kStmtTokens{Token::kTokRead, Token::kTokPrint,
                                     Token::kTokCall, Token::kTokWhile,
                                     Token::kTokIf,   Token::kTokIdent};

const std::unordered_set<Token> kRelationTokens{
    Token::kTokAnd,     Token::kTokOr,           Token::kTokLess,
    Token::kTokGreater, Token::kTokGreaterEqual, Token::kTokLessEqual,
    Token::kTokEquiv,   Token::kTokNotEqual};

const std::unordered_set<Token>
    kKeyWordTokens{Token::kTokProcedure, Token::kTokRead,
                   Token::kTokPrint, Token::kTokCall,
                   Token::kTokWhile, Token::kTokIf,
                   Token::kTokThen, Token::kTokElse,
                   Token::kTokIdent};

const char kProcedure[] = "procedure";
const char kRead[] = "read";
const char kPrint[] = "print";
const char kWhile[] = "while";
const char kCall[] = "call";
const char kIf[] = "if";
const char kElse[] = "else";
const char kThen[] = "then";
const char kLess[] = "<";
const char kLessEqual[] = "<=";
const char kGreater[] = ">";
const char kGreaterEqual[] = ">=";
const char kEqualTo[] = "==";
const char kNotEqual[] = "!=";
const char kAnd[] = "&&";
const char kOr[] = "||";
const char kNot[] = "!";
const char kOpenCurly[] = "{";
const char kCloseCurly[] = "}";
const char kSemicolon[] = ";";
const char kOpenBracket[] = "(";
const char kCloseBracket[] = ")";
const char kEquals[] = "=";
const char kPlus[] = "+";
const char kMinus[] = "-";
const char kTimes[] = "*";
const char kDiv[] = "/";
const char kMod[] = "%";

const std::unordered_map<Token, std::string> kTokenToStringMap{
    {Token::kTokEof, "eof"},

    {Token::kTokProcedure, kProcedure},
    {Token::kTokRead, kRead},
    {Token::kTokPrint, kPrint},
    {Token::kTokCall, kCall},
    {Token::kTokWhile, kWhile},
    {Token::kTokIf, kIf},
    {Token::kTokElse, kElse},
    {Token::kTokThen, kThen},

    {Token::kTokIdent, "variable"},
    {Token::kTokInteger, "integer"},

    {Token::kTokOpenCurly, kOpenCurly},
    {Token::kTokCloseCurly, kCloseCurly},
    {Token::kTokSemicolon, kSemicolon},
    {Token::kTokOpenBracket, kOpenBracket},
    {Token::kTokCloseBracket, kCloseBracket},

    {Token::kTokEquals, kEquals},
    {Token::kTokPlus, kPlus},
    {Token::kTokMinus, kMinus},
    {Token::kTokTimes, kTimes},
    {Token::kTokDiv, kDiv},
    {Token::kTokMod, kMod},

    // relations
    {Token::kTokLess, kLess},
    {Token::kTokGreater, kGreater},
    {Token::kTokGreaterEqual, kGreaterEqual},
    {Token::kTokLessEqual, kLessEqual},
    {Token::kTokEquiv, kEqualTo},
    {Token::kTokNotEqual, kNotEqual},

    // conditions
    {Token::kTokOr, kOr},
    {Token::kTokAnd, kAnd},
    {Token::kTokNot, kNot},

    // error
    {Token::kTokError, "error"},
};


const std::unordered_map<std::string, Token> kStringToTokenMap{
    {kProcedure, Token::kTokProcedure},
    {kRead, Token::kTokRead},
    {kPrint, Token::kTokPrint},
    {kCall, Token::kTokCall},
    {kWhile, Token::kTokWhile},
    {kIf, Token::kTokIf},
    {kElse, Token::kTokElse},
    {kThen, Token::kTokThen},

    {kOpenCurly, Token::kTokOpenCurly},
    {kCloseCurly, Token::kTokCloseCurly},
    {kSemicolon, Token::kTokSemicolon},
    {kOpenBracket, Token::kTokOpenBracket},
    {kCloseBracket, Token::kTokCloseBracket},

    {kEquals, Token::kTokEquals},
    {kPlus, Token::kTokPlus},
    {kMinus, Token::kTokMinus},
    {kTimes, Token::kTokTimes},
    {kDiv, Token::kTokDiv},
    {kMod, Token::kTokMod},

    // relations
    {kLess, Token::kTokLess},
    {kGreater, Token::kTokGreater},
    {kGreaterEqual, Token::kTokGreaterEqual},
    {kLessEqual, Token::kTokLessEqual},
    {kEqualTo, Token::kTokEquiv},
    {kNotEqual, Token::kTokNotEqual},

    // conditions
    {kOr, Token::kTokOr},
    {kAnd, Token::kTokAnd},
    {kNot, Token::kTokNot},
};

bool IsStmtToken(Token input) { return kStmtTokens.count(input); }

bool IsKeyWordToken(Token token) { return kKeyWordTokens.count(token) == 1; }

bool IsRelationToken(Token token) { return kRelationTokens.count(token) == 1; }

std::string TokenToString(Token token) {
  return kTokenToStringMap.at(token);
}

bool IsTokenString(std::string str) {
  return kStringToTokenMap.count(str);
}

Token StringToToken(std::string str) {
  return kStringToTokenMap.at(str);
}
}  // namespace sp
