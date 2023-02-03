#include <catch.hpp>

#include "QPS/preprocessor/Parser.h"

using namespace qps; // NOLINT

TEST_CASE("Test Parser") {
  Parser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, \"x+y\")";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that", "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "\"x+y\"", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, \"x+y\")";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }

  SECTION("Test ParseQuery") {
    std::string query_string = "variable p; select p";
    parser.ParseQuery(query_string);
  };

  SECTION("Validation methods") {
    REQUIRE(Parser::is_ident("a") == true);
    REQUIRE(Parser::is_ident("abc") == true);
    REQUIRE(Parser::is_ident("abc0123") == true);
    REQUIRE(Parser::is_ident("1") == false);
    REQUIRE(Parser::is_ident("a&") == false);
  };
}
