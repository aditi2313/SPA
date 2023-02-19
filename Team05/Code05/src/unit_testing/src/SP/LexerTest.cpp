#include <string>
#include <vector>
#include <catch.hpp>

#include "SP/lexer/Lexer.h"
#include "common/exceptions/SP.h"
#include "models/AST/Token.h"

using sp::Lexer;
using sp::Token;

void TestLexerForToken(std::string vals, std::vector<Token> tokens);
void TestLexerForWords(std::string vals, std::vector<std::string> result);
void TestLexerForInts(std::string input, std::vector<int> result);

TEST_CASE("Testing lexer functionality") {
  SECTION("Test relational functionality") {
    TestLexerForToken(
        "< == <= && || != !",
        {Token::kTokLess, Token::kTokEquiv, Token::kTokLessEqual,
         Token::kTokAnd, Token::kTokOr, Token::kTokNotEqual, Token::kTokNot});
  }

  SECTION("Test relational functionality without spaces") {
    TestLexerForToken(
        "< == <=&&||!=!",
        {Token::kTokLess, Token::kTokEquiv, Token::kTokLessEqual,
         Token::kTokAnd, Token::kTokOr, Token::kTokNotEqual, Token::kTokNot});
  }

  SECTION("Test ident functionality") {
    TestLexerForToken("read procedure value if while print",
                      {Token::kTokRead, Token::kTokProcedure, Token::kTokIdent,
                       Token::kTokIf, Token::kTokWhile, Token::kTokPrint});
  }

  SECTION("Test single char functionality") {
    TestLexerForToken("{ } ! < > ()",
                      {Token::kTokOpenCurly, Token::kTokCloseCurly,
                       Token::kTokNot, Token::kTokLess, Token::kTokGreater,
                       Token::kTokOpenBracket, Token::kTokCloseBracket});
  }

  SECTION("Test no spacing functionality") {
    TestLexerForToken("{}!<>()||&&!=",
                      {Token::kTokOpenCurly, Token::kTokCloseCurly,
                       Token::kTokNot, Token::kTokLess, Token::kTokGreater,
                       Token::kTokOpenBracket, Token::kTokCloseBracket,
                       Token::kTokOr, Token::kTokAnd, Token::kTokNotEqual});
  }

  SECTION("Test simple procedure functionality") {
    // procedure will always be treated as kTokProcedure
    // To allow procedure to be the name for a procedure,
    // the respective parsers chooses to treat them as
    // variable names
    std::string test =
        "procedure procedure {"
        "read x;"
        "print y;"
        "read y;"
        "lemon }"
        "-100";

    std::vector<Token> tokens{
        Token::kTokProcedure, Token::kTokProcedure,  Token::kTokOpenCurly,
        Token::kTokRead,      Token::kTokIdent,      Token::kTokSemicolon,
        Token::kTokPrint,     Token::kTokIdent,      Token::kTokSemicolon,
        Token::kTokRead,      Token::kTokIdent,      Token::kTokSemicolon,
        Token::kTokIdent,     Token::kTokCloseCurly, Token::kTokMinus,
        Token::kTokInteger,   Token::kTokEof};
    TestLexerForToken(test, tokens);
  }

  SECTION("Test simple word reading") {
    std::vector<std::string> words{"a", "word", "lemon"};
    TestLexerForWords(" a word lemon ", words);
  }

  SECTION("Test more reading") {
    std::string input =
        "Lorem ipsum dolor sit amet\n"
        "consectetur adipiscing elit\n"
        "Sed vitae ante tellus read print\n";
    std::vector<std::string> words{
        "Lorem",       "ipsum",      "dolor", "sit",  "amet",
        "consectetur", "adipiscing", "elit",  "Sed",  "vitae",
        "ante",        "tellus",     "read",  "print"};
    TestLexerForWords(input, words);
  }
}

TEST_CASE("Integer reading test cases") {
  SECTION("Positive test cases") {
    TestLexerForInts("1000 10000 15 0 1 1", {1000, 10000, 15, 0, 1, 1});
  }
}

TEST_CASE("Error reading cases") {
  SECTION("Unsupported tokens") {
    // a is needed as the lexer pre processes the first token.
    // which means the exception would be thrown in construction.
    Lexer lxr("a ##@");
    REQUIRE_THROWS_AS(lxr.GetTokAndIncrement(), sp::LexerException);
  }

  SECTION("Unsupport ints (leading zeroes)") {
    Lexer lxr("a 01000");
    REQUIRE_THROWS_AS(lxr.GetTokAndIncrement(), sp::LexerException);
  }
}

TEST_CASE("Lexer checking for double condition") {
  SECTION("Basic checking") {
    Lexer lxr("(a + c) || (a - b)");
    REQUIRE(lxr.IsDoubleCond());
  }
  SECTION("Single cond") {
    Lexer lxr("((x) >= b)");
    REQUIRE(!lxr.IsDoubleCond());
  }
  SECTION("Nested conditions") {
    Lexer lxr("(((a - c + d))) || (((x - 123)) < (102))");
    REQUIRE(lxr.IsDoubleCond());
  }

  SECTION("Long conditions") {
    Lexer lxr("(a + b - c * (d + l) > 1000) && (100 / 1000 < 203)");
    REQUIRE(lxr.IsDoubleCond());
  }
  SECTION("Nested cond") {
    Lexer lxr("((a > 100) && (b < 100)) || (!(a < 100))");
    REQUIRE(lxr.IsDoubleCond());
  }

  SECTION("A relation") {
    Lexer lxr("(a + b) <= (a -b)");
    REQUIRE(!lxr.IsDoubleCond());
  }
  SECTION("A not") {
    Lexer lxr("!((a == 1) && (b == 2))");
    REQUIRE(!lxr.IsDoubleCond());
  }

  SECTION("Not within a  double cond") {
    Lexer lxr("(a == 1) || (!(b == 2)) && (b == 3)");
    REQUIRE(lxr.IsDoubleCond());
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

void TestLexerForWords(std::string vals, std::vector<std::string> result) {
  Lexer lxr(vals);
  auto curr = result.begin();
  while (curr != result.end()) {
    std::string val = lxr.get_ident();
    lxr.Increment();
    REQUIRE(*curr == val);
    curr++;
  }
}

void TestLexerForInts(std::string input, std::vector<int> result) {
  auto curr = result.begin();
  Lexer lxr(input);
  while (curr != result.end()) {
    int v = lxr.get_integer();
    REQUIRE(lxr.GetTokAndIncrement() == Token::kTokInteger);
    REQUIRE(v == *curr);
    curr++;
  }
}
