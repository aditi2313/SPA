#include <catch.hpp>

#include "QPS/models/Query.h"

using namespace qps; // NOLINT

TEST_CASE("Test Query methods") {
  Query query;
  SECTION("Test synonyms methods") {
    query.declare_synonym("v", EntityType::kVariable);
    REQUIRE(query.is_synonym_name_declared("v"));
    REQUIRE(query.get_declared_synonym_entity_type("v")
                == EntityType::kVariable);

    // Unknown key
    REQUIRE(query.is_synonym_name_declared("unknown") == false);
  };
}
