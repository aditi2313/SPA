#include <catch.hpp>
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT

// TODO(JL): replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryResult") {
  SECTION("Intersect") {
    QueryResultPtr result1 = std::make_unique<QueryResult>();
    QueryResultPtr result2 = std::make_unique<QueryResult>();

    result1->IntersectWith(result2);
    REQUIRE(result1->is_empty());
  };
}
