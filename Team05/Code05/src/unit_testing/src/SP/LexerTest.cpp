#include <catch.hpp>
#include <string>
#include <vector>

#include "SP/lexer/Lexer.h"
#include "models/AST/Token.h"

using sp::Lexer;
using sp::Token;

void TestLexerForToken(std::string vals, std::vector<Token> tokens);

TEST_CASE("Testing lexer functionality") {
  SECTION("Test relational functionality") {
    TestLexerForToken(
        "< == <= && || != !",
        {Token::kTokLess, Token::kTokEquiv, Token::kTokLessEqual,
         Token::kTokAnd, Token::kTokOr, Token::kTokNotEqual, Token::kTokNot});
  }

  SECTION("Test ident functionality") {
    TestLexerForToken(
        "read procedure value",
        {Token::kTokRead, Token::kTokProcedure, Token::kTokIdent});
  }

  SECTION("Test single char functionality") {
    TestLexerForToken("{ } ! < > ()",
                      {Token::kTokOpenCurly, Token::kTokCloseCurly,
                       Token::kTokNot, Token::kTokLess, Token::kTokGreater,
                       Token::kTokOpenBracket, Token::kTokCloseBracket});
  }
}

void TestLexerForToken(std::string vals, std::vector<Token> tokens) {
  Lexer lxr(vals);
  Token tok;
  auto curr = tokens.begin();
  while ((tok = lxr.GetTokAndIncrement()) != Token::kTokEof &&
         curr != tokens.end()) {
    REQUIRE(*curr == tok);
    curr++;
  }
}
