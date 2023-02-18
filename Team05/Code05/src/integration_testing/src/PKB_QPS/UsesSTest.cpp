//// NOTE: first argument for Uses cannot be wildcard
//// Add testcases for
//// UsesS (s, _)
//
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

using uses_data = std::pair<int, std::unordered_set<std::string>>;
// Helper method for testing
std::unique_ptr<PKBRead> InitializeUPKB(std::vector<uses_data> data) {
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

  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test PKB and QPS integration for UsesS clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializeUPKB({
      {10, {"a", "b", "c"}},
      {20, {"d", "e"}},
      {30, {"f"}},
  });

  SECTION("Uses(IntArg, VarSynonym) should return correct results") {
    std::string query_string = "variable v; Select v such that Uses(10, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Uses(StmtSynonym, VarSynonym) should return "
      "correct results when select s.") {
    std::string query_string = "stmt s; variable v;"
        "Select s such that Uses(s, v) ";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Uses(StmtSynonym, VarSynonym) should return correct results when "
      "select s with only one var") {
    std::string query_string =
        "stmt s; variable v; Select s such that Uses(s, a)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10"};
    REQUIRE(actual_results == expected_results);
  }
  SECTION(
      "Uses(StmtSynonym, VarSynonym) should return correct results "
      "when select s.") {
    std::string query_string =
        "stmt s; variable v; Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }

    SECTION("Uses(StmtSynonym, VarSynonym) should return correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Modifies(StmtSynonym, VarSynonym) should return " 
      "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }

    SECTION("Uses(IntArg, VarSynonym) should return " 
        "correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("Modifies(IntArg, VarSynonym) should return "
      "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Uses(IntArg, WILDCARD) should return correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Modifies(IntArg, WILDCARD) should return correct results when select "
      "s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(10, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Uses(Stmtsynonym, VarSynonym) should "
      "return correct results when select v") {
    std::string query_string =
        "variable v; stmt s; "
        "Select v such that Uses(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Modifies(Stmtsynonym, VarSynonym) should return "
      "correct results when select s") {
    std::string query_string =
        "variable v; stmt s; "
        "Select s such that Uses(s, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"10", "20", "30"};
    REQUIRE(actual_results == expected_results);
  }
}
