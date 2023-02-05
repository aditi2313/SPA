#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using qps::Formatter;
using qps::QueryResult;

// Helper function for testing
QueryResult BuildQueryResult(std::list<models::EntityStub> entities) {
  QueryResult query_result;
  for (models::EntityStub entity : entities) {
    query_result.add_query_result(entity);
  }
  return query_result;
}

// TODO(JL): replace with real unit tests after EntityStub is implemented
TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    models::EntityStub stmt;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({stmt}));
    REQUIRE(actual.front() == "abc");
  };
  SECTION("For variables") {
    models::EntityStub var;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({var}));
    REQUIRE(actual.front() == "abc");
  };
  SECTION("For procedures") {
    models::EntityStub procedure;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({procedure}));
    REQUIRE(actual.front() == "abc");
  };
  SECTION("For constants") {
    models::EntityStub constant;
    std::list<std::string> actual =
        query_formatter.FormatQuery(BuildQueryResult({constant}));
    REQUIRE(actual.front() == "abc");
  };
}
