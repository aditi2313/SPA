#include <catch.hpp>

#include "QPS/preprocessor/ParseState.h"
#include "QPS/models/PQL.h"
#include "common/Exceptions.h"

using namespace qps; // NOLINT

// Helper method for testing
void TestErrorCase(ParseState &state, std::vector<std::string> tokens) {
  std::unique_ptr<Query> query = std::make_unique<Query>();
  auto itr = tokens.begin();
  REQUIRE_THROWS_AS(
      state.parse(tokens, itr, query), PqlSyntaxErrorException);
}

TEST_CASE("Test DeclarationParseState") {
  DeclarationParseState state;

  SECTION("Single declaration should parse correctly") {
    std::vector<std::string> tokens{"variable", "v", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);

    REQUIRE(query->does_synonym_exist(
        Synonym("v", PQL::kVariableEntityName)));
    REQUIRE(itr == tokens.end());
  };

  SECTION("Multiple declarations should parse correctly") {
    std::vector<std::string> tokens{
        "variable", "v1", ",", "v2", ",", "v3", ";"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);

    REQUIRE(query->does_synonym_exist(
        Synonym("v1", PQL::kVariableEntityName)));
    REQUIRE(query->does_synonym_exist(
        Synonym("v2", PQL::kVariableEntityName)));
    REQUIRE(query->does_synonym_exist(
        Synonym("v3", PQL::kVariableEntityName)));
    REQUIRE(itr == tokens.end());
  };


  SECTION("Invalid design entity identifier should "
          "throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"var", "v", ";"});
  }

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  }

  SECTION("Missing semi-colon should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"variable", "v"});
  }

  SECTION("Invalid ident should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"variable", "01234", ";"});
  }
}

TEST_CASE("Test SelectParseState") {
  SelectParseState state;
  SECTION("Select synonym should parse correctly") {
    std::vector<std::string> tokens{"Select", "v"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);

    REQUIRE(query->get_selected_synonyms().at(0) == "v");
    REQUIRE(itr == tokens.end());
  }
  // TODO(JL): Add some error cases here
}

TEST_CASE("Test SuchThatParseState") {
  SuchThatParseState state;
  SECTION("Such that clause for Modifies should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Modifies", "(", "6", ",", "v", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_clause = ModifiesClause(
        query->CreateArgument("6"),
        query->CreateArgument("v"));

    Clause *actual_clause =
        query->get_clauses().at(0).get();

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for Follows should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Follows", "(", "6", ",", "7", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_clause = FollowsClause(
        query->CreateArgument("6"),
        query->CreateArgument("7"));

    Clause *actual_clause =
        query->get_clauses().at(0).get();

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Such that clause for FollowsT should parse correctly") {
    std::vector<std::string> tokens{
        "such", "that", "Follows*", "(", "6", ",", "10", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_clause = FollowsTClause(
        query->CreateArgument("6"),
        query->CreateArgument("7"));

    Clause *actual_clause =
        query->get_clauses().at(0).get();

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Wrong casing should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"such", "that", "MODIFIES", "(", "6", ",", "v", ")"});
  }

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  }

  SECTION("Missing semi-colon should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"Modifies", "(", "6", ",", "v", ")"});
  }

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"Modifies", "(", "6", ",", "v", ";"});
  }
}

TEST_CASE("Test PatternParseState") {
  PatternParseState state;
  SECTION("Pattern clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "_", ",", "\"x + y\"", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_modifies_clause = ModifiesClause(
        query->CreateArgument("a"),
        query->CreateArgument("_"));
    auto expected_pattern_clause = PatternClause(
        query->CreateArgument("a"),
        query->CreateArgument("\"x + y\""));

    REQUIRE(*(query->get_clauses().at(0)) == expected_modifies_clause);
    REQUIRE(*(query->get_clauses().at(1)) == expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "v", ",", "_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_modifies_clause = ModifiesClause(
        query->CreateArgument("a"),
        query->CreateArgument("v"));
    auto expected_pattern_clause = PatternClause(
        query->CreateArgument("a"),
        query->CreateArgument("_"));

    REQUIRE(*(query->get_clauses().at(0)) == expected_modifies_clause);
    REQUIRE(*(query->get_clauses().at(1)) == expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Pattern wildcard clause should parse correctly") {
    std::vector<std::string> tokens{
        "pattern", "a", "(", "variable", ",", "_\"x\"_", ")"};
    std::unique_ptr<Query> query = std::make_unique<Query>();
    auto itr = tokens.begin();
    state.parse(tokens, itr, query);
    auto expected_modifies_clause = ModifiesClause(
        query->CreateArgument("a"),
        query->CreateArgument("variable"));
    auto expected_pattern_clause = PatternClause(
        query->CreateArgument("a"),
        query->CreateArgument("_\"x\"_"));

    REQUIRE(*(query->get_clauses().at(0)) == expected_modifies_clause);
    REQUIRE(*(query->get_clauses().at(1)) == expected_pattern_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Wrong casing should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"PATTERN", "a", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Empty tokens should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {});
  };

  SECTION("Missing syn-assign should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "(", "_", ",", "x + y", ")"});
  };

  SECTION("Missing bracket should throw PqlSyntaxErrorException") {
    TestErrorCase(state, {"pattern", "(", "_", ",", "x + y"});
  };
}

