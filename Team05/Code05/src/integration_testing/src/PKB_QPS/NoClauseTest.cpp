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

// TODO(JL and Gab): PKB endpoint not yet implemented
// Example tests:
// variable v; Select v
// Returns a list of all variable names in the program

// procedure p; Select p
// Returns a list of all procedure names in the program

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKB(
    std::vector<std::string> variables
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  for (auto var : variables) {
    pkb_write.add_variable(var);
  }

  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test PKB and QPS integration for Select with no clauses") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKB(
      {
          {"x", "y", "z"}
      });

  SECTION("Get all variables from PKB") {
    std::string query_string = "variable v; Select v";
    std::list<std::string> actual_results;

    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"x", "y", "z"};

    REQUIRE(actual_results == expected_results);
  }
}
