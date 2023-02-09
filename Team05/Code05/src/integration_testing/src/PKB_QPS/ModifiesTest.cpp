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

using modifies_data = std::pair<int, std::vector<std::string>>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKB(
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
  }

  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test PKB and QPS integration for Modifies clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKB(
      {
          {10, {"a", "b", "c"}},
          {25, {"somebody"}},
          {30, {"once", "told", "me"}}
      });

  SECTION("Modifies(statement, variable) should return correct results 1") {
    std::string query_string = "variable v; Select v such that Modifies(10, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"a", "b", "c"};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Modifies(statement, variable) should return correct results 2") {
    std::string query_string = "variable v; Select v such that Modifies(25, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"somebody"};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Modifies(statement, variable) should return correct results 3") {
    std::string query_string = "variable v; Select v such that Modifies(30, v)";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"me", "once", "told"};

    REQUIRE(actual_results == expected_results);
  }
}
