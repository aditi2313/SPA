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

// Helper method for testing (Forward Declaration)
std::unique_ptr<PKBRead> InitializePKBForFollows(
    std::vector<follows_data> data
);

TEST_CASE("Test PKB and QPS integration for FollowsT clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForFollows(
      {
          {10, 11},
          {11, 12},
          {12, 13}
      });

  SECTION("FollowsT(IntArg, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(10, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(Wildcard, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(_, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(synonym, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(s, 13)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(IntArg, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(10, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(Wildcard, synonym) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(_, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(synonym, synonym) should return correct results") {
    std::string query_string = "stmt s1, s2; "
                               "Select s1 such that Follows*(s1, s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(IntArg, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(Wildcard, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(_, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("FollowsT(synonym, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Follows*(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(actual_results == expected_results);
  }
}
