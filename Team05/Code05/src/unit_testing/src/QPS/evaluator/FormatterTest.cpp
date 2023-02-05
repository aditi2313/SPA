#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using qps::Formatter;
using qps::QueryResult;

// Helper function for testing
QueryResult BuildQueryResult(std::list<models::Entity> entities) {
  QueryResult query_result;
  for (models::Entity entity : entities) {
    query_result.add_query_result(entity);
  }
  return query_result;
}

// TODO(JL): replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    models::Entity stmt;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({stmt}));
    REQUIRE(actual.front() == "");
  };
  SECTION("For variables") {
    models::Entity var;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({var}));
    REQUIRE(actual.front() == "");
  };
  SECTION("For procedures") {
    models::Entity procedure;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({procedure}));
    REQUIRE(actual.front() == "");
  };
  SECTION("For constants") {
    models::Entity constant;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({constant}));
    REQUIRE(actual.front() == "");
  };
}
