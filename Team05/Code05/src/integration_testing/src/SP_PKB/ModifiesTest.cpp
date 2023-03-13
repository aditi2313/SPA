#include <catch.hpp>
#include <unordered_set>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

std::unordered_map<std::variant<int, std::string>,
                   std::unordered_set<std::string>>
InitializeModifies(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ModifiesPredicateFilter>(
      [](pkb::ModifiesData data) { return true; });
  auto results_ptr = reader.Modifies(std::move(ftr));
  auto results_table = results_ptr->get_result();

  std::unordered_map<std::variant<int, std::string>,
                     std::unordered_set<std::string>>
      results;

  for (auto result : results_table->get_indexes()) {
    auto data = results_table->get_row(result);
    for (auto v : data.get_variables()) {
      results[data.get_index()].insert(v);
    }
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Modifies data") {
  SECTION("Assign statement - 1 modifies x") {
    std::string program = "procedure modifies { x = x; }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {"modifies", {"x"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Assign statement - 1 modifies x") {
    std::string program = "procedure modifies { x = y; }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {"modifies", {"x"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Read statement - relationship holds") {
    std::string program = "procedure modifies { read x; }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {"modifies", {"x"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Print statement - relationship does not hold") {
    std::string program = "procedure uses { print x; }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship holds") {
    std::string program = "procedure modifies { while (x == y) { read z; } }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"z"}}, {2, {"z"}}, {"modifies", {"z"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop - transitive condition holds") {
    std::string program =
        "procedure modifies { while (x > y) { while (z == 3) { read v; } } }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {
            {1, {"v"}}, {2, {"v"}}, {3, {"v"}}, {"modifies", {"v"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop with print statement - empty table") {
    std::string program =
        "procedure modifies { while (x > y) { while (z == 3) { print v; } } }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Calls statement") {
    std::string program =
        "procedure modifies { read x; call helper; } procedure helper { while "
        "(z "
        "> 5) { read v; } }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}},
                            {3, {"v"}},
                            {4, {"v"}},
                            {"helper", {"v"}},
                            {"modifies", {"x"}}};

    REQUIRE(actual_results == expected_results);
  }
}
