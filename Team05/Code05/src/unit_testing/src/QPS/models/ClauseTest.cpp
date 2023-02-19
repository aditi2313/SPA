#include <catch.hpp>
#include "QPS/models/Query.h"
#include "QPS/models/Clause.h"

using namespace qps; // NOLINT

// TODO(JL): replace with real unit tests after PKB is implemented
TEST_CASE("Test Clause") {
  SECTION("Modifies clause should compare equal") {
    QueryPtr query = std::make_unique<Query>();
    auto clause_1 = ModifiesClause(
        query->CreateArgument("\"abc\""),
        query->CreateArgument("\"def\""));
    auto clause_2 = ModifiesClause(
        query->CreateArgument("\"abc\""),
        query->CreateArgument("\"def\""));

    REQUIRE(clause_1 == clause_2);
  };

  SECTION("Different clause types with same arguments "
          "should not compare equal") {
    QueryPtr query = std::make_unique<Query>();
    auto modifies_clause = ModifiesClause(
        query->CreateArgument("123"),
        query->CreateArgument("456"));

    auto pattern_clause = PatternClause(
        query->CreateArgument("123"),
        query->CreateArgument("456"));

    REQUIRE(modifies_clause != pattern_clause);
  }
}
