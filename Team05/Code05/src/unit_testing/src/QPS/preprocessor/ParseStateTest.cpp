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
    auto itr = state.parse(tokens, tokens.begin(), query);

    REQUIRE(query.get_synonym("v") == models::EntityStub());
    REQUIRE(itr == tokens.end());
  };

  SECTION("Error cases") {
    std::vector<std::string> invalid_tokens{"var", "v", ";"};
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);

    invalid_tokens = {}; // empty
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);

    invalid_tokens = {"variable", "v"}; // missing semi-colon
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);

    invalid_tokens = {"variable", "01234", ";"}; // invalid ident
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);
  }
}

TEST_CASE("Test SuchThatParseState") {
  SuchThatParseState state;
  Query query;
  SECTION("Happy path") {
    std::vector<std::string> tokens{"such", "that", "Modifies", "(", "6", ",", "v", ")"};
    auto itr = state.parse(tokens, tokens.begin(), query);
    auto expected_clause = ModifiesClause(Argument("6"), Argument("v"));

    ModifiesClause *actual_clause = dynamic_cast<ModifiesClause *>(std::move(query.get_clauses().at(0)).get());

    REQUIRE(*actual_clause == expected_clause);
    REQUIRE(itr == tokens.end());
  };

  SECTION("Error cases") {
    // Error cases
    // Wrong casing
    std::vector<std::string> invalid_tokens{"such", "that", "MODIFIES", "(", "6", ",", "v", ")"};
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);

    invalid_tokens = {}; // empty
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);

    invalid_tokens = {"Modifies", "(", "6", ",", "v", ")"}; // missing such-that
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);
    
    invalid_tokens = {"Modifies", "(", "6", ",", "v"}; // missing bracket
    REQUIRE_THROWS_AS(state.parse(invalid_tokens, invalid_tokens.begin(), query),
                      PqlSyntaxErrorException);
  }
}
