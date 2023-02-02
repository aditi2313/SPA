#include <catch.hpp>
#include "models/results/QueryResult.h"

using namespace models; // NOLINT

// TODO(JL): replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryResult") {
  SECTION("Intersect") {
    QueryResult result1;
    QueryResult result2;

    result1.IntersectWith(result2);
    REQUIRE(result1.is_empty());
  };
}
