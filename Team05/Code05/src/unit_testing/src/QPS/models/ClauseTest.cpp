#include <catch.hpp>
#include "QPS/models/Clause.h"

using namespace qps; // NOLINT

// TODO(JL): replace with real unit tests after PKB is implemented
TEST_CASE("Test Clause") {
  SECTION("Clause Equality") {
    auto clause_1 = ModifiesClause(
        Argument("abc"), Argument("def"));
    auto clause_2 = ModifiesClause(
        Argument("abc"), Argument("def"));

    REQUIRE(clause_1 == clause_2);

    clause_2 = ModifiesClause(
        Argument("123"), Argument("456"));

    REQUIRE(clause_1 != clause_2);

    auto pattern_clause = PatternClause(
        Argument("123"), Argument("456"));

    REQUIRE(clause_1 != pattern_clause);
  };

}
