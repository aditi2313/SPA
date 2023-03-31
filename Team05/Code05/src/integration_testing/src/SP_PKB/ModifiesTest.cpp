#include <catch.hpp>

#include "Utility.h"
#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/Export.h"
#include "common/filter/filters/Export.h"

std::unordered_map<std::variant<int, std::string>,
                   std::unordered_set<std::string>>
InitializeModifies(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  filter::ModifiesPredicateFilter filter(TruePredicate<pkb::ModifiesData>());
  auto& results_table = reader.Modifies(filter);

  std::unordered_map<std::variant<int, std::string>,
                     std::unordered_set<std::string>>
      results;

  while (!results_table.reached_end()) {
    auto& data = results_table.read_data();
    for (auto v : data.get_variables()) {
      results[data.get_index()].insert(v);
    }
    results_table.increment();
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

    std::unordered_set<std::string> vars({"v", "x"});

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {2, {"v"}},        {3, {"v"}},
                            {4, {"v"}}, {"helper", {"v"}}, {"modifies", vars}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Multiple calls statements") {
    std::string program =
        "procedure modifies { read x; call helper1; call helper2; } procedure "
        "helper1 { read y; } procedure helper2 { read z; call helper1; }";

    auto actual_results = InitializeModifies(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}},
                            {2, {"y"}},
                            {3, {"y", "z"}},
                            {4, {"y"}},
                            {5, {"z"}},
                            {6, {"y"}},
                            {"modifies", {"x", "y", "z"}},
                            {"helper1", {"y"}},
                            {"helper2", {"y", "z"}}};

    REQUIRE(actual_results == expected_results);
  }
}

TEST_CASE("Test calls within modifies") {
  std::string program =
      "procedure p1 {"
      "if (x == 2) then {"
      "m = 2;"
      "}else {"
      "call r1;"
      "n = 3;"
      "}"
      "}"
      "procedure r1 { k = 1; }";
  auto actual_results = InitializeModifies(program);

  std::unordered_map<std::variant<int, std::string>,
                     std::unordered_set<std::string>>
      expected_results = {
          {1, {"k", "m", "n"}},    {2, {"m"}}, {3, {"k"}},   {4, {"n"}},
          {"p1", {"k", "m", "n"}}, {5, {"k"}}, {"r1", {"k"}}};
  REQUIRE(actual_results == expected_results);
}
