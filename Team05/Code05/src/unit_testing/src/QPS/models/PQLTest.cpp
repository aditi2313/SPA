#include <catch.hpp>
#include "QPS/models/PQL.h"

using qps::PQL; // NOLINT

// TODO(JL): replace with real unit tests after PKB is implemented
TEST_CASE("Test PQL") {
  SECTION("Validation methods") {
    REQUIRE(PQL::is_ident("a") == true);
    REQUIRE(PQL::is_ident("abc") == true);
    REQUIRE(PQL::is_ident("abc0123") == true);
    REQUIRE(PQL::is_ident("1") == false);
    REQUIRE(PQL::is_ident("a&") == false);

    REQUIRE(PQL::is_integer("10") == true);
    REQUIRE(PQL::is_integer("1234567890") == true);
    REQUIRE(PQL::is_integer("0") == false);
    REQUIRE(PQL::is_integer("01") == false);
  };
}

