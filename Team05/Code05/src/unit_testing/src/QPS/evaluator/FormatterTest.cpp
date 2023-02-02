#include <catch.hpp>
#include "QPS/evaluator/Formatter.h"

using namespace qps; // NOLINT

// Helper function for testing
QueryResult BuildQueryResult(std::vector<models::EntityStub> entities) {
  QueryResult query_result;
  for (models::EntityStub entity : entities) {
    query_result.add_query_result(entity);
  }
  return query_result;
}

// TODO(JL): replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    models::EntityStub stmt;
    std::vector<std::string> actual = query_formatter.FormatQuery(
        BuildQueryResult({stmt}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For variables") {
    models::EntityStub var;
    std::vector<std::string> actual = query_formatter.FormatQuery(
        BuildQueryResult({var}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For procedures") {
    models::EntityStub procedure;
    std::vector<std::string> actual = query_formatter.FormatQuery(
        BuildQueryResult({procedure}));
    REQUIRE(actual[0] == "abc");
  };
  SECTION("For constants") {
    models::EntityStub constant;
    std::vector<std::string> actual = query_formatter.FormatQuery(
        BuildQueryResult({constant}));
    REQUIRE(actual[0] == "abc");
  };
}

