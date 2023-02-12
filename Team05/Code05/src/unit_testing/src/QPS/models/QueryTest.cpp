#include <catch.hpp>

#include "QPS/models/Query.h"

using namespace qps; // NOLINT

TEST_CASE("Test Query methods") {
  Query query;
  SECTION("Test synonyms methods") {
    query.declare_synonym("v", PQL::kVariableEntityId);
    REQUIRE(query.does_synonym_exist(Synonym("v", PQL::kVariableEntityId)));

    // Unknown key
    REQUIRE(query.does_synonym_exist(Synonym("unknown", PQL::kVariableEntityId)) == false);
  };
}
