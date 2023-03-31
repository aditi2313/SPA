#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/Export.h"
#include "common/filter/filters/Export.h"

std::unordered_map<int, std::unordered_set<int>> InitializeNext(
    std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  filter::NextPredicateFilter ftr(
      [](pkb::NextData data) { return true; });
  auto& results_table = reader.Next(ftr);

  std::unordered_map<int, std::unordered_set<int>> results;

  while (!results_table.reached_end()) {
    auto data = results_table.read_data();
    for (auto v : data.get_next_im_list()) {
      results[data.get_index()].insert(v);
    }
    results_table.increment();
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Next data") {
  SECTION("One statement - empty table") {
    std::string program = "procedure next { x = 3; }";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two statements") {
    std::string program = "procedure next { x = 5; read x; }";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Three statements") {
    std::string program = "procedure next { x = 5; read x; print x; }";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}, {2, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement") {
    std::string program =
        "procedure next { if (x == 0) then { x = 5; } else { y = 3; } }";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested while loop") {
    std::string program =
        "procedure next { while (x > 5) { read x; while (y < 3) { read y; } } "
        "}";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2}}, {2, {3}}, {3, {1, 4}}, {4, {3}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Calls statement within if") {
    std::string program =
        "procedure next { if (x == 3) then { call helper1; } else { call "
        "helper2; } } procedure helper1 { x = 3; } procedure helper2 { y = 5; "
        "read z; }";

    auto actual_results = InitializeNext(program);

    std::unordered_map<int, std::unordered_set<int>> expected_results = {
        {1, {2, 3}}, {5, {6}}};

    REQUIRE(actual_results == expected_results);
  }
}
