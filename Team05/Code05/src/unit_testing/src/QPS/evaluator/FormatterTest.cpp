#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("Single selected synonym") {
    std::vector<std::vector<Entity>> selected_entities =
        {{Entity(1)}};
    QueryResultPtr query_result = std::make_unique<ListQueryResult>(
        selected_entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1");
  };

  SECTION("Multiple selected synonyms") {
    std::vector<std::vector<Entity>> selected_entities =
        {{Entity(1), Entity(2)}};
    QueryResultPtr query_result = std::make_unique<ListQueryResult>(
        selected_entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1 2");
  };
}
