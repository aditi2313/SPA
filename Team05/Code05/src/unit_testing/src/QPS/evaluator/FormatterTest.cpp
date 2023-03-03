#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    EntitySet entities;
    entities.insert(Entity(1));
    std::vector<EntitySet> selected_entities = {entities};
    QueryResultPtr query_result = std::make_unique<ListQueryResult>(
        selected_entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1");
  };
}
