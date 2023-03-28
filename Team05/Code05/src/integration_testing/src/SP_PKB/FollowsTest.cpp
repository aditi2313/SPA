#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/FollowsVisitor.h"
#include "common/filter/filters/Export.h"

std::unordered_map<int, std::unordered_set<int>> InitializeFollows(
    std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));  
  filter::FollowsPredicateFilter ftr(
      [](pkb::FollowsData data) { return true; });
  
  auto& results_table = reader.Follows(ftr);

  std::unordered_map<int, std::unordered_set<int>> results;

  while (!results_table.reached_end()) {
    auto data = results_table.read_data();
    for (auto v : data.get_follows_list()) {
      results[data.get_index()].insert(v);
    }
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Follows data") {
  SECTION("One statement - empty table") {
    std::string program = "procedure follows { read x; }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two read statements - relationship holds") {
    std::string program = "procedure follows { read x; read y; }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two assign statements - relationship holds") {
    std::string program = "procedure follows { x = 5; y = 3; }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two while loops - relationship does not hold for their stmtlsts") {
    std::string program =
        "procedure follows { while (i > 0) { i = i - 1; } while (j < 0) { "
        "j = j + 1; } }";
    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship does not hold") {
    std::string program = "procedure follows { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement - relationship only holds in same stmtlst") {
    std::string program =
        "procedure follows { if (x < 0) then { read x; read y; } else { "
        "read z; } "
        "}";
    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {2, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two procedures - relationship does not hold") {
    std::string program =
        "procedure follows { x = 5; } procedure readfollows2 { y = 3; }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Three read statements - transitive relationship holds") {
    std::string program = "procedure follows { read x; read y; read z; }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}, {2, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop - relationship only holds in same stmtlst") {
    std::string program =
        "procedure follows { while (x > 5) { print x; while (y > 3) { read y; "
        "print y; } } }";

    auto actual_results = InitializeFollows(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {2, {3}}, {4, {5}}};

    REQUIRE(actual_results == expected_results);
  }
}
