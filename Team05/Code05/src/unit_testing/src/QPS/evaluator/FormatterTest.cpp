#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

// TODO(JL): replace with real unit tests after Entity is implemented
TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    EntityPtrList entities;
    entities.push_back(std::make_unique<Stmt>(1));
    QueryResultPtr query_result = std::make_unique<QueryResult>(entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(std::move(query_result));
    REQUIRE(actual.front() == "1");
  };
//  SECTION("For variables") {
//    models::Entity var;
//    std::list<std::string> actual =
//        query_formatter.FormatQuery(BuildQueryResult({var}));
//    REQUIRE(actual.front() == "");
//  };
//  SECTION("For procedures") {
//    models::Entity procedure;
//    std::list<std::string> actual =
//        query_formatter.FormatQuery(BuildQueryResult({procedure}));
//    REQUIRE(actual.front() == "");
//  };
//  SECTION("For constants") {
//    models::Entity constant;
//    std::list<std::string> actual =
//        query_formatter.FormatQuery(BuildQueryResult({constant}));
//    REQUIRE(actual.front() == "");
//  };
}
