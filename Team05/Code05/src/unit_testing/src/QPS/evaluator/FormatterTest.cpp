#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("Single selected synonym") {
    EntitySet entities;
    entities.insert(Entity(1));
    std::vector<EntitySet> selected_entities = {entities};
    QueryResultPtr query_result = std::make_unique<ListQueryResult>(
        selected_entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1");
  };

  SECTION("Multiple selected synonyms") {
    EntitySet entities1, entities2;
    entities1.insert(Entity(1));
    entities2.insert(Entity(2));
    std::vector<EntitySet> selected_entities = {entities1, entities2};
    QueryResultPtr query_result = std::make_unique<ListQueryResult>(
        selected_entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1, 2");
  };
}
