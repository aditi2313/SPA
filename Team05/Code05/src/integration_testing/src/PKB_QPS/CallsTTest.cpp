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

using calls_data = std::pair<std::string, std::vector<std::string>>;

// Helper method for testing, forward declaration
std::unique_ptr<PKBRead> InitializePKBForCalls(
    std::vector<calls_data> data
);

TEST_CASE("Test PKB and QPS integration for CallsT clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForCalls(
      {
          {"proc1", {"proc2"}},
          {"proc2", {"proc3"}},
          {"proc3", {"proc4"}},
      });

  SECTION("Calls*(IdentArg, IdentArg) should return correct results") {
    std::string query_string = "procedure p; "
                               "Select p "
                               "such that Calls*(\"proc1\", \"proc2\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{
        "proc1", "proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(SynArg, SynArg) should return correct results") {
    std::string query_string = "procedure p; Select p such that Calls*(p, p)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(Wildcard, IdentArg) should return correct results") {
    std::string query_string = "procedure p; "
                               "Select p such that Calls*(_, \"proc3\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(ProcSyn, IdentArg) should return correct results") {
    std::string query_string = "procedure p; "
                               "Select p such that Calls*(p, \"proc2\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(IdentArg, ProcSyn) should return correct results") {
    std::string query_string = "procedure p; "
                               "Select p such that Calls*(\"proc1\", p)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(Wildcard, ProcSyn) should return correct results") {
    std::string query_string = "procedure p; Select p such that Calls*(_, p)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(ProcSyn, ProcSyn) should return correct results") {
    std::string query_string = "procedure p1, p2; "
                               "Select p1 such that Calls*(p1, p2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(ProcSyn, ProcSyn) with both synonyms selected"
          "should return correct results") {
    std::string query_string = "procedure p1, p2; "
                               "Select <p1, p2> such that Calls*(p1, p2)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{
        "proc1 proc2", "proc1 proc3", "proc1 proc4",
        "proc2 proc3", "proc2 proc4",
        "proc3 proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(IdentArg, Wildcard) should return correct results") {
    std::string query_string = "procedure p; "
                               "Select p such that Calls*(\"proc1\", _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(Wildcard, Wildcard) should return correct results") {
    std::string query_string = "procedure p; Select p such that Calls*(_, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3", "proc4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Calls*(ProcSyn, Wildcard) should return correct results") {
    std::string query_string = "procedure p; Select p such that Calls*(p, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}

