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

using usesS_data = std::pair<int, std::unordered_set<std::string>>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForUsesS(std::vector<usesS_data> data) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [line, variables] : data) {
    pkb_write.AddUsesData(line, variables);
    for (auto var : variables) {
      pkb_write.add_variable(var);
    }
    pkb_write.add_stmt(line);
  }

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

// NOTE: first argument for Uses cannot be wildcard
TEST_CASE("Test PKB and QPS integration for UsesS clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForUsesS(
      {
          {10, {"a", "b", "c"}},
          {20, {"d", "e"}},
          {30, {"f"}},
      });

  SECTION("Uses(IntArg, VarSynonym) should return correct results") {
    std::string query_string = "variable v; Select v such that Uses(10, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(StmtSynonym, VarSynonym) should return "
          "correct results when select s.") {
    std::string query_string = "stmt s; variable v;"
                               "Select s such that Uses(s, v) ";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(StmtSynonym, VarSynonym) should return "
          "correct results when select multiple synonyms") {
    std::string query_string = "stmt s; variable v;"
                               "Select <s, v> such that Uses(s, v) ";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{
        "10 a", "10 b", "10 c", "20 d", "20 e", "30 f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(StmtSynonym, VarSynonym) should return correct results when "
      "select s with only one var") {
    std::string query_string =
        "stmt s; variable v; Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(StmtSynonym, VarSynonym) should return correct results "
      "when select s") {
    std::string query_string =
        "stmt s; variable v; Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(StmtSynonym, VarSynonym) should return correct "
          "results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(StmtSynonym, VarSynonym) should return "
          "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(IntArg, VarSynonym) should return "
          "correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Uses(IntArg, VarSynonym) should return "
          "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(IntArg, WILDCARD) should return correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(IntArg, WILDCARD) should return correct results when select "
      "s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(StmtSynonym, VarSynonym) should "
      "return correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION(
      "Uses(StmtSynonym, VarSynonym) should return "
      "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}
