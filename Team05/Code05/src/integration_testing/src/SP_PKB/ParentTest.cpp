#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ParentVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

std::unordered_map<int, std::unordered_set<int>> InitializeParent(
    std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ParentPredicateFilter>(
      [](pkb::ParentData data) { return true; });
  auto results_table = reader.Parent(std::move(ftr));

  std::unordered_map<int, std::unordered_set<int>> results;

  for (auto result : results_table->get_indexes()) {
    auto data = results_table->get_row(result);
    for (auto v : data.get_all_children()) {
      results[data.get_index()].insert(v);
    }
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Parent Data") {
  SECTION("One statement - empty table") {
    std::string program = "procedure parent { read x; }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two read statements - empty table") {
    std::string program = "procedure parent { read x; read y; }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship holds") {
    std::string program = "procedure parent { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement - relationship holds for then and else stmtlsts") {
    std::string program =
        "procedure parent { if (x == 0) then { read x; } else { read y; } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested while loop - transitive relationship holds") {
    std::string program =
        "procedure parent { while (y > 5) { while (x < 3) { read z; } } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}, {2, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Triple nested while loop - transitive relationship holds") {
    std::string program =
        "procedure parent { while (x > 3) { while (x < 3) { while (x == 3) { "
        "read while; } } } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3, 4}}, {2, {3, 4}}, {3, {4}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested if statement - transitive relationship holds") {
    std::string program =
        "procedure parent { if (x > 5) then { if (z > 5) then { read y; } else "
        "{ read x; } } else { if (y > 5) then { read x; } else { read y; } } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3, 4, 5, 6, 7}}, {2, {3, 4}}, {5, {6, 7}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two loops within a loop - relationship holds only in same branch") {
    std::string program =
        "procedure parent { while (y == 2) { if (x == 2) then { read x; } else "
        "{ read y; } while (x > 2) { read z; } } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3, 4, 5, 6}}, {2, {3, 4}}, {5, {6}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Two if statements - relationship only holds for same branch and "
      "statement") {
    std::string program =
        "procedure parent { if (x == 0) then { read x; } else { read y; } if "
        "(y == x) then { read y; } else { read x; } }";

    auto actual_results = InitializeParent(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}, {4, {5, 6}}};

    REQUIRE(actual_results == expected_results);
  }
}
