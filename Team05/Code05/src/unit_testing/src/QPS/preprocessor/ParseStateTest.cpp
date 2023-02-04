#include <catch.hpp>

#include "QPS/preprocessor/ParseState.h"
#include "common/Exceptions.h"

using namespace qps; // NOLINT

// TODO(jl): Replace EntityStub
TEST_CASE("Test DeclarationParseState") {
  DeclarationParseState state;
  Query query;
  SECTION("Happy path") {
    std::vector<std::string> tokens{"variable", "v", ";"};
    auto itr = state.parse(tokens, tokens.begin(), &query);

    REQUIRE(query.get_synonym("v") == models::EntityStub());
    REQUIRE(itr == tokens.end());
  };

  SECTION("Error cases") {
    // invalid design entity identifier
    std::vector<std::string> invalid_tokens{"var", "v", ";"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // empty
    invalid_tokens = {};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // missing semi-colon
    invalid_tokens = {"variable", "v"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // invalid ident
    invalid_tokens = {"variable", "01234", ";"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);
  }
}

TEST_CASE("Test SynonymParseState") {
  SynonymParseState state;
  Query query;
  SECTION("Happy path") {
    std::vector<std::string> tokens{"Select", "v"};
    auto itr = state.parse(tokens, tokens.begin(), &query);

    REQUIRE(query.get_selected_synonyms().at(0) == "v");
    REQUIRE(itr == tokens.end());
  }
}

TEST_CASE("Test SuchThatParseState") {
  SuchThatParseState state;
  Query query;
  SECTION("Happy path") {
    std::vector<std::string> tokens{
        "such", "that", "Modifies", "(", "6", ",", "v", ")"};
    auto itr = state.parse(tokens, tokens.begin(), &query);
    auto expected_clause = ModifiesClause(Argument("6"), Argument("v"));

    Clause *actual_clause =
        query.get_clauses().at(0).get();

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Error cases") {
    // wrong casing
    std::vector<std::string> invalid_tokens{
        "such", "that", "MODIFIES", "(", "6", ",", "v", ")"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // empty
    invalid_tokens = {};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // missing bracket
    invalid_tokens = {"Modifies", "(", "6", ",", "v", ")"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // missing bracket
    invalid_tokens = {"Modifies", "(", "6", ",", "v"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);
  }
}

TEST_CASE("Test PatternParseState") {
  PatternParseState state;
  Query query;
  SECTION("Happy path") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"x + y\"", ")"};
    auto itr = state.parse(tokens, tokens.begin(), &query);
    auto expected_clause = PatternClause(Argument("_"), Argument("\"x + y\""));

    PatternClause *actual_clause = dynamic_cast<PatternClause *>(
        std::move(query.get_clauses().at(0)).get());

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Error cases") {
    // wrong casing
    std::vector<std::string> invalid_tokens{
        "PATTERN", "a", "(", "_", ",", "x + y", ")"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // empty
    invalid_tokens = {};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // missing syn-assign
    invalid_tokens = {"pattern", "(", "_", ",", "x + y", ")"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);

    // missing bracket
    invalid_tokens = {"pattern", "(", "_", ",", "x + y"};
    REQUIRE_THROWS_AS(
        state.parse(invalid_tokens, invalid_tokens.begin(), &query),
        PqlSyntaxErrorException);
  }
}

