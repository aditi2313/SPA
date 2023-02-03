#include <catch.hpp>

#include "QPS/preprocessor/ParseState.h"
#include "common/Exceptions.h"

using namespace qps; // NOLINT

// TODO(jl): Replace EntityStub
TEST_CASE("Test Declaration Parse State") {
  DeclarationParseState state;
  Query query;
  SECTION("One declaration statement") {
    // Happy path
    std::vector<std::string> tokens{"variable", "v", ";"};
    auto itr = state.parse(tokens, tokens.begin(), query);

    REQUIRE(query.get_synonym("v") == models::EntityStub());
    REQUIRE(itr == tokens.end());

    // Error cases
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
  };
}
