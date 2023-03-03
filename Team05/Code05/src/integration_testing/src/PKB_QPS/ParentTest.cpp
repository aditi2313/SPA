#include <memory>
#include <string>
#include <vector>
#include <list>
#include <catch.hpp>

#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "PKB/PKBRead.h"
#include "QPS/QPS.h"

using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using parent_data = std::pair<int, int>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForParent(std::vector<parent_data> data) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line, line2] : data) {
    pkb_write.AddParentData(line, line2);
    pkb_write.add_stmt(line);
    pkb_write.add_stmt(line2);
  }

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

TEST_CASE("Test PKB and QPS integration for valid Parent clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForParent(
      {
          {1, 2},
          {2, 3},
          {3, 4},
          {4, 5},
          {5, 6}
      });

  SECTION("Parent(IntArg, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(1,2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(WILDCARD, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(_,2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(IntArg, WILDCARD) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(1,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(synonym, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(s,6)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"5"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(Intarg, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(1,s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(synoym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2; Select s1 such that Parent(s1,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(synoym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2; Select s2 such that Parent(s1,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(WILDCARD, synonym) should return correct results") {
    std::string query_string = "stmt s2; Select s2 such that Parent(_,s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(synoym, WILDCARD) should return correct results") {
    std::string query_string = "stmt s1; Select s1 such that Parent(s1,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Parent(WILDCARD, WILDCARD) should return correct results") {
    std::string query_string = "stmt s; Select s such that Parent(_,_)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{"1", "2", "3", "4", "5", "6"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}

TEST_CASE("Test PKB and QPS integration for Invalid Parent clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForParent({{1, 2}, {2, 3}});
  SECTION(
      "Parent(IntArg, IntArg) where one arg is not in the pkb should "
      "be empty") {
    std::string query_string = "stmt s; Select s such that Parent(1,1024)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Parent(IntArg, IntArg) where they are not bounded by Parent should "
      "be empty") {
    std::string query_string = "stmt s; Select s such that Parent(1,3)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Parent(IntArg, IntArg) where they are not bounded by Parent should "
      "be empty") {
    std::string query_string = "stmt s; Select s such that Parent(2,1)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);
    std::list<std::string> expected_results{};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}
