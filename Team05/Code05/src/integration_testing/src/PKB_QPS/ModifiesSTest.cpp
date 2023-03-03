#include <memory>
#include <string>
#include <unordered_set>
#include <list>
#include <catch.hpp>

#include "common/Utiity.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "PKB/PKBRead.h"
#include "QPS/QPS.h"

using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using modifies_data = std::pair<int, std::unordered_set<std::string>>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForModifies(
    std::vector<modifies_data> data
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line, variables] : data) {
    pkb_write.AddModifiesData(line, variables);
    for (auto var : variables) {
      pkb_write.add_variable(var);
    }
    pkb_write.add_stmt(line);
  }

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

// Note: First argument for ModifiesS clause cannot be wildcard
TEST_CASE("Test PKB and QPS integration for ModifiesS clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForModifies(
      {
          {10, {"a", "b", "c"}},
          {25, {"d", "e"}},
          {30, {"f"}},
      });

  SECTION("Modifies(IntArg, VarSynonym) should return correct results") {
    std::string query_string = "variable v; Select v such that Modifies(10, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(StmtSynonym, VarSynonym) should return correct results") {
    std::string query_string = "variable v; stmt s; "
                               "Select v such that Modifies(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(StmtSynonym, VarSynonym) with Select <s, v> "
          "should return correct results") {
    std::string query_string = "variable v; stmt s; "
                               "Select <s, v> such that Modifies(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{
        "10, a", "10, b", "10, c", "25, d", "25, e", "30, f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(StmtSynonym, VarSynonym) should return correct results") {
    std::string query_string = "variable v; stmt s; "
                               "Select s such that Modifies(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "25", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(IntArg, IdentArg) should return correct results") {
    std::string query_string = "variable v; "
                               "Select v such that Modifies(10, \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(StmtSynonym, IdentArg) should return correct results") {
    std::string query_string = "stmt s; Select s such that Modifies(s, \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(IntArg, Wildcard) should return correct results") {
    std::string query_string = "variable v; stmt s; "
                               "Select v such that Modifies(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(StmtSynonym, Wildcard) should return correct results") {
    std::string query_string = "stmt s; Select s such that Modifies(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "25", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}

