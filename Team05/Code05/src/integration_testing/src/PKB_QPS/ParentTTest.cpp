#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "QPS/QPS.h"

#include <catch.hpp>
#include <list>
#include <memory>
#include <string>
#include <vector>
using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using parentT_data = std::pair<int, int>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePTPKB(std::vector<parentT_data> data) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line, line2] : data) {
    pkb_write.AddParentData(line, line2);
    pkb_write.add_stmt(line);
    pkb_write.add_stmt(line2);
  }

  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test PKB and QPS integration for valid ParentT clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePTPKB({
      {1, 2},
      {3, 4},
      {5, 6},
      {2, 3},
      {4, 5},
  });

  SECTION("ParentT(IntArg, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(1,2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(WILDCARD, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(_,2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(IntArg, WILDCARD) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(1,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(synonym, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(s,6)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(IntArg, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(1,s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(synoym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2;"
        "Select s1 such that Parent*(s1,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5"};
    REQUIRE(actual_results == expected_results);
  }
  SECTION("ParentT(synoym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2;"
        "Select s2 such that Parent*(s1,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("ParentT(WILDCARD, synonym) should return correct results") {
    std::string query_string = "stmt s2; Select s2 such that Parent*(_,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }
  SECTION("ParentT(synoym, WILDCARD) should return correct results") {
    std::string query_string = "stmt s1; Select s1 such that Parent*(s1,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5"};
    REQUIRE(actual_results == expected_results);
  }
  SECTION("Parent(WILDCARD, WILDCARD) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(_,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(actual_results == expected_results);
  }
}

TEST_CASE("Test PKB and QPS integration for Invalid ParentT clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePTPKB({{1, 2}, {2, 3}});
  SECTION(
      "ParentT(IntArg, IntArg) where one arg is not in the pkb should "
      "return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(1,4)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{};
    REQUIRE(actual_results == expected_results);
  }
  SECTION(
      "ParentT(IntArg, IntArg) where they are not bounded by Parent should "
      "return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(2,1)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{};
    REQUIRE(actual_results == expected_results);
  }
}

TEST_CASE("Test PKB and QPS integration for Valid ParentT clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePTPKB({{1, 2}, {2, 3}});
  SECTION(
      "Parent(IntArg, IntArg) where one arg is not in the pkb should "
      "return correct results") {
    std::string query_string = "stmt s; Select s such that Parent*(1,3)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3"};
    REQUIRE(actual_results == expected_results);
  }
}
