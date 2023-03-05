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

using next_data = std::pair<int, int>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForNext(
    std::vector<next_data> data
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line1, line2] : data) {
    pkb_write.AddNextData(line1, line2);
    pkb_write.add_stmt(line1);
    pkb_write.add_stmt(line2);
  }

  return std::make_unique<PKBRead>(
      pkb_write.ProcessTableAndEndWrite());
}

TEST_CASE("Test PKB and QPS integration for Next clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForNext(
      {
          {10, 11},
          {11, 12},
          {12, 13},
      });

  SECTION("Next(IntArg, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(10, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(SynArg, SynArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(s, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(Wildcard, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(_, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(StmtSyn, IntArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(s, 11)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(IntArg, StmtSyn) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(10, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(Wildcard, StmtSyn) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(_, s)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"11", "12", "13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(StmtSyn, StmtSyn) should return correct results") {
    std::string query_string = "stmt s1, s2; "
                               "Select s1 such that Next(s1, s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(StmtSyn, StmtSyn) with multiple select"
          "should return correct results") {
    std::string query_string = "stmt s1, s2; "
                               "Select <s1, s2> such that Next(s1, s2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10 11", "11 12", "12 13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(IntArg, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(Wildcard, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(_, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12", "13"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Next(StmtSyn, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Next(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "11", "12"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}
