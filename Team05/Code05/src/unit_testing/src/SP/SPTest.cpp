#include <string>
#include <vector>
#include <catch.hpp>

#include "SP/Lexer.h"
#include "models/AST/Token.h"

using sp::Lexer;
using sp::Token;

void TestLexerForToken(std::string vals, std::vector<Token> tokens);

TEST_CASE("Testing lexer functionality") {
  SECTION("Test relational functionality") {
    TestLexerForToken("< = <= &&", {Token::kTokLess, Token::kTokEquals,
                                    Token::kTokLessEqual, Token::kTokAnd});
  }
}

void TestLexerForToken(std::string vals, std::vector<Token> tokens) {
  Lexer lxr(vals);
  int tok;
  auto curr = tokens.begin();
  while ((tok = lxr.GetTokAndIncrement()) != Token::kTokEof &&
         curr != tokens.end()) {
    REQUIRE(*curr == tok);
    curr++;
  }
}
