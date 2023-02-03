#include <catch.hpp>

#include "QPS/preprocessor/Parser.h"

using namespace qps; // NOLINT

TEST_CASE("Test Parser") {
  Parser parser;
  SECTION("Validation methods") {
    REQUIRE(Parser::is_ident("a") == true);
    REQUIRE(Parser::is_ident("abc") == true);
    REQUIRE(Parser::is_ident("abc0123") == true);
    REQUIRE(Parser::is_ident("1") == false);
    REQUIRE(Parser::is_ident("a&") == false);
  };
}
