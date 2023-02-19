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

using follows_data = std::pair<int, int>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForFollows(
    std::vector<follows_data> data
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line, line2] : data) {
    pkb_write.AddFollowsData(line, line2);
    pkb_write.add_stmt(line);
    pkb_write.add_stmt(line2);
  }

  return std::make_unique<PKBRead>(
    pkb_write.ProcessTableAndEndWrite());
}

TEST_CASE("Test PKB and QPS integration for Follows clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForFollows(
      {
          {10, 11},
          {11, 12},
          {12, 13},
      });

  SECTION("Follows(IntArg, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(10, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(Wildcard, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(_, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(synonym, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(s, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(IntArg, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(10, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(Wildcard, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(_, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(synonym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2; "
                               "Select s1 such that Follows(s1, s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(IntArg, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(Wildcard, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(_, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(synonym, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(actual_results == expected_results);
  }
}

