#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

TEST_CASE("Test QueryFormatter") {
  SECTION("Single selected synonym") {
    std::vector<std::vector<Entity>> selected_entities =
        {{Entity(1)}};
    std::unique_ptr<ListQueryResult> query_result =
        std::make_unique<ListQueryResult>(selected_entities);
    std::list<std::string> actual =
        Formatter::FormatListQuery(
            query_result->get_query_results());
    REQUIRE(actual.front() == "1");
  };

  SECTION("Multiple selected synonyms") {
    std::vector<std::vector<Entity>> selected_entities =
        {{Entity(1), Entity(2)}};
    std::unique_ptr<ListQueryResult> query_result =
        std::make_unique<ListQueryResult>(selected_entities);
    std::list<std::string> actual =
        Formatter::FormatListQuery(
            query_result->get_query_results());
    REQUIRE(actual.front() == "1 2");
  };
}
