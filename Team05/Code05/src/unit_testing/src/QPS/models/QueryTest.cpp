#include <catch.hpp>

#include "QPS/models/Query.h"

using namespace qps; // NOLINT

TEST_CASE("Test Query methods") {
  Query query;
  
  // TODO(jl): Replace EntityStub
  SECTION("Test synonyms methods") {
    query.set_synonym("syn", models::EntityStub());
    REQUIRE(query.get_synonym("syn") == models::EntityStub());

    // Unknown key
    REQUIRE_THROWS_AS(query.get_synonym("unknown"), std::out_of_range);

    // Already previously declared
    REQUIRE(query.set_synonym("syn", models::EntityStub()) == false);
  };
}
