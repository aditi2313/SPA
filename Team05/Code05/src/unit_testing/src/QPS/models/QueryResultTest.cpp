#include <iostream>
#include <catch.hpp>
#include "QPS/models/QueryResult.h"

using namespace qps; // NOLINT

// Helper method for testing
EntityPtrList BuildStmtList(std::vector<int> stmts) {
  EntityPtrList result;
  for(int stmt : stmts) {
    result.push_back(std::make_unique<Stmt>(stmt));
  }
  return result;
}

bool CompareEntityPtrList(const EntityPtrList &LHS, const EntityPtrList &RHS) {
  if(LHS.size() != RHS.size()) return false;
  for(int N = LHS.size(), i = 0; i < N; ++i) {
    if(*LHS.at(i) != *RHS.at(i)) return false;
  }
  return true;
}

TEST_CASE("Test QueryResult") {
  SECTION("Intersect with empty list should be empty list") {
    EntityPtrList list1 = BuildStmtList({1, 2, 3});
    ListQueryResultPtr result1 = std::make_unique<ListQueryResult>(list1);
    ListQueryResult result2;

    result1->IntersectWith(result2);
    REQUIRE(result1->is_empty());
  };

  SECTION("Intersect two lists should have correct elements") {
    // Not necessarily sorted
    EntityPtrList list1 = BuildStmtList({6, 5, 4, 3, 2, 1});
    ListQueryResultPtr result1 = std::make_unique<ListQueryResult>(list1);
    EntityPtrList list2 = BuildStmtList({2, 7, 10, 4, 8, 6});
    ListQueryResult result2 = ListQueryResult(list2);

    result1->IntersectWith(result2);

    EntityPtrList expected_list = BuildStmtList({2, 4, 6});
    REQUIRE(CompareEntityPtrList(result1->get_query_results(), expected_list));
  };
}
