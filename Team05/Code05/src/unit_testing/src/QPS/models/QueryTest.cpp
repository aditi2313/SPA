#include <catch.hpp>

#include "QPS/models/Query.h"

using namespace qps; // NOLINT

TEST_CASE("Test Query methods") {
  Query query;
  SECTION("Test synonyms methods") {
    query.declare_synonym("v", PQL::kVariableEntityName);
    REQUIRE(query.is_synonym_declared(
        Synonym("v", PQL::kVariableEntityName)));

    // Unknown key
    REQUIRE(query.is_synonym_declared(
        Synonym("unknown", PQL::kVariableEntityName)) == false);
  };
}
