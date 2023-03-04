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

using modifiesP_data = std::pair<std::string, std::unordered_set<std::string>>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKBForModifiesP(
    std::vector<modifiesP_data> data
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto [proc, variables] : data) {
    pkb_write.AddModifiesData(proc, variables);
    for (auto var : variables) {
      pkb_write.add_variable(var);
    }
    pkb_write.add_procedure(proc);
  }

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

// Note: First argument for ModifiesS clause cannot be wildcard
TEST_CASE("Test PKB and QPS integration for ModifiesP clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKBForModifiesP(
      {
          {"proc1", {"a", "b", "c"}},
          {"proc2", {"d", "e"}},
          {"proc3", {"f"}},
      });

  SECTION("Modifies(IdentArg, VarSynonym) should return correct results") {
    std::string query_string = "variable v; Select v such that Modifies(\"proc1\", v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(ProcSynonym, VarSynonym) should return correct results") {
    std::string query_string = "procedure p; variable v;"
                               "Select v such that Modifies(p, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(ProcSynonym, VarSynonym) with Select <p, v> "
          "should return correct results") {
    std::string query_string = "variable v; procedure p; "
                               "Select <p, v> such that Modifies(p, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{
        "proc1 a", "proc1 b", "proc1 c", "proc2 d", "proc2 e", "proc3 f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(ProcSynonym, VarSynonym) should return correct results") {
    std::string query_string = "variable v; procedure p; "
                               "Select p such that Modifies(p, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(IdentArg, IdentArg) should return correct results") {
    std::string query_string = "variable v; "
                               "Select v such that Modifies(\"proc1\", \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(ProcSynonym, IdentArg) should return correct results") {
    std::string query_string = "procedure p; Select p such that Modifies(p, \"a\")";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(IdentArg, Wildcard) should return correct results") {
    std::string query_string = "variable v; "
                               "Select v such that Modifies(\"proc1\", _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c", "d", "e", "f"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("Modifies(ProcSynonym, Wildcard) should return correct results") {
    std::string query_string = "procedure p; Select p such that Modifies(p, _)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"proc1", "proc2", "proc3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}

