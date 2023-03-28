#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/Export.h"
#include "common/filter/filters/Export.h"

std::unordered_map<std::variant<int, std::string>,
                   std::unordered_set<std::string>>
InitializeUses(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  filter::UsesPredicateFilter ftr([](pkb::UsesData data) { return true; });
  auto& results_table = reader.Uses(ftr);

  std::unordered_map<std::variant<int, std::string>,
                     std::unordered_set<std::string>>
      results;
  while (!results_table.reached_end()) {
    auto& data = results_table.read_data();
    for (auto v : data.get_variables()) {
      results[data.get_index()].insert(v);
    }
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Uses data") {
  SECTION("Assign statement - 1 uses x") {
    std::string program = "procedure uses { x = x; }";

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {"uses", {"x"}}};

    auto actual_results = InitializeUses(program);

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Assign statement - 1 uses y") {
    std::string program = "procedure uses { x = y; }";

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"y"}}, {"uses", {"y"}}};
    auto actual_results = InitializeUses(program);

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Read statement - relationship does not hold") {
    std::string program = "procedure uses { read x; }";

    auto actual_results = InitializeUses(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Print statement - relationship holds") {
    std::string program = "procedure uses { print x; }";

    auto actual_results = InitializeUses(program);

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {"uses", {"x"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement - relationship holds for cond") {
    std::string program =
        "procedure uses { if (((x == y) && (z > 3)) || (read < print)) then { "
        "read z; } else { print v; } }";

    auto actual_results = InitializeUses(program);

    std::unordered_set<std::string> vars({"v", "x", "y", "z", "read", "print"});

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, vars}, {3, {"v"}}, {"uses", vars}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop - transitive condition holds") {
    std::string program =
        "procedure uses { while (x > y) { while (z == 3) { read v; } } }";

    auto actual_results = InitializeUses(program);

    std::unordered_set<std::string> vars({"x", "y", "z"});

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, vars}, {2, {"z"}}, {"uses", vars}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Calls statement") {
    std::string program =
        "procedure uses { print x; call helper; } procedure helper { while (z "
        "> 5) { print v; } }";

    auto actual_results = InitializeUses(program);

    std::unordered_set<std::string> vars({"v", "z"});
    std::unordered_set<std::string> vars2({"v", "x", "z"});

    std::unordered_map<std::variant<int, std::string>,
                       std::unordered_set<std::string>>
        expected_results = {{1, {"x"}}, {2, vars},        {3, vars},
                            {4, {"v"}}, {"helper", vars}, {"uses", vars2}};

    REQUIRE(actual_results == expected_results);
  }
}

TEST_CASE("Test calls within uses") {
  std::string program =
      "procedure p1 {"
      "if (x == 2) then {"
      "call r1;"
      "}else {"
      "m = 2;"
      "n = 3;"
      "}"
      "}"
      "procedure r1 { print k; }";
  auto actual_results = InitializeUses(program);

  std::unordered_map<std::variant<int, std::string>,
                     std::unordered_set<std::string>>
      expected_results = {{1, {"x", "k"}},
                          {2, {"k"}},
                          {"p1", {"x", "k"}},
                          {5, {"k"}},
                          {"r1", {"k"}}};
  REQUIRE(actual_results == expected_results);
}
