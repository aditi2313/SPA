#include <iostream>
#include <catch.hpp>
#include "QPS/models/QueryResult.h"
#include "common/Utiity.h"

using namespace qps; // NOLINT

// Helper method for testing
EntitySet BuildStmtList(std::vector<int> stmts) {
  EntitySet result;
  for (int stmt : stmts) {
    result.insert(Entity(stmt));
  }
  return result;
}

TEST_CASE("Test QueryResult") {
  SECTION("Intersect with empty list should be empty list") {
    EntitySet list1 = BuildStmtList({1, 2, 3});
    QueryResultPtr result1 = std::make_unique<QueryResult>(list1);
    QueryResult result2;

    result1->IntersectWith(result2);
    REQUIRE(result1->is_empty());
  };

  SECTION("Intersect two lists should have correct elements") {
    // Not necessarily sorted
    EntitySet list1 = BuildStmtList({6, 5, 4, 3, 2, 1});
    QueryResultPtr result1 = std::make_unique<QueryResult>(list1);
    EntitySet list2 = BuildStmtList({2, 7, 10, 4, 8, 6});
    QueryResult result2 = QueryResult(list2);

    result1->IntersectWith(result2);

    EntitySet expected_list = BuildStmtList({2, 4, 6});
    REQUIRE(result1->get_query_results() == expected_list);
  };
}
