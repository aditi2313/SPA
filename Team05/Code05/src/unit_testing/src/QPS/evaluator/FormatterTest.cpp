#include <memory>
#include <catch.hpp>


#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using qps::Formatter;
using qps::QueryResult;

// Helper function for testing
QueryResult BuildQueryResult(std::vector<models::Entity> entities) {
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
    std::vector<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({stmt}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For variables") {
    models::Entity var;
    std::vector<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({var}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For procedures") {
    models::Entity procedure;
    std::vector<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({procedure}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For constants") {
    models::Entity constant;
    std::vector<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({constant}));
    REQUIRE(actual[0] == "abc");
  };
}
