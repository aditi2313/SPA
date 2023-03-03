#include <memory>
#include <string>
#include <unordered_set>
#include <list>
#include <catch.hpp>

#include "PKB/PKBWrite.h"
#include "PKB/PKBRead.h"
#include "QPS/QPS.h"

using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using modifies_data = std::pair<int, std::unordered_set<std::string>>;

// Helper method for testing. Forward declared.
std::unique_ptr<PKBRead> InitializePKBForModifies(
    std::vector<modifies_data> data
);

TEST_CASE("Test PKB and QPS integration for BOOLEAN clauses") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForModifies(
      {
          {10, {"a", "b", "c"}},
          {25, {"d", "e"}},
          {30, {"f"}},
      });


  SECTION("Select BOOLEAN such that Modifies(StmtSynonym, VarSynonym) "
          "should return correct results") {
    std::string query_string = "variable v; stmt s; "
                               "Select BOOLEAN such that Modifies(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"TRUE"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Select BOOLEAN such that Modifies(IntArg, IdentArg) "
          "should return correct results") {
    std::string query_string = "variable v; "
                               "Select BOOLEAN such that Modifies(10, \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"TRUE"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Select BOOLEAN such that Modifies(IntArg, IdentArg) "
          "for false clause should return correct results") {
    std::string query_string = "variable v; "
                               "Select BOOLEAN such that Modifies(10, \"d\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"FALSE"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Select BOOLEAN such that Modifies(IntArg, IdentArg) "
          "where BOOLEAN is a synonym should return correct results") {
    std::string query_string = "stmt BOOLEAN; "
                               "Select BOOLEAN such that "
                               "Modifies(BOOLEAN, \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}

