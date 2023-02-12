#include <memory>
#include <catch.hpp>

#include "QPS/evaluator/Formatter.h"
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT
using namespace models;  // NOLINT

TEST_CASE("Test QueryFormatter") {
  Formatter query_formatter;

  SECTION("For statements") {
    EntityPtrList entities;
    entities.push_back(std::make_unique<Stmt>(1));
    QueryResultPtr query_result = std::make_unique<QueryResult>(entities);
    std::list<std::string> actual =
        query_formatter.FormatQuery(query_result);
    REQUIRE(actual.front() == "1");
  };
}
