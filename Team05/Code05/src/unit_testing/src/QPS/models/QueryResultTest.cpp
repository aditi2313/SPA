#include "catch.hpp"
#include "QPS/models/QueryResult.h"

using namespace qps;

// TODO: replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryResult") {

  SECTION("Intersect") {
    QueryResult result1;
    QueryResult result2;

    result1.Intersect(result2);
    REQUIRE(result1.is_empty());
  };
}