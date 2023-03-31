#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/Export.h"
#include "common/filter/filters/Export.h"

std::unordered_map<std::string, std::unordered_set<std::string>>
InitializeCalls(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  filter::CallsPredicateFilter ftr(
      [](pkb::CallsData data) { return true; });
  auto& results_table = reader.Calls(ftr);

  std::unordered_map<std::string, std::unordered_set<std::string>> results;

  while (!results_table.reached_end()) {
    auto data = results_table.read_data();
    for (auto v : data.get_total_calls()) {
      results[data.get_index()].insert(v);
    }
    results_table.increment();
  }

  return results;
}

TEST_CASE("Test SP and PKB integration for Calls data") {
  SECTION("Single procedure, no calls - no entry") {
    std::string program =
        "procedure calls { call = 5; if (call == call) then { print call; } "
        "else { read call; while (call > 0) { x = call; } } print calls; }";

    auto actual_results = InitializeCalls(program);

    std::unordered_map<std::string, std::unordered_set<std::string>>
        expected_results = {};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Single calls statement") {
    std::string program =
        "procedure calls { call helper; } procedure helper { x = 1; }";

    auto actual_results = InitializeCalls(program);

    std::unordered_map<std::string, std::unordered_set<std::string>>
        expected_results = {{"calls", {"helper"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Multiple calls statements") {
    std::string program =
        "procedure calls { call helper1; call helper2; } procedure helper1 { x "
        "= 5; } procedure helper2 { call helper1; y = 3; }";

    auto actual_results = InitializeCalls(program);

    std::unordered_map<std::string, std::unordered_set<std::string>>
        expected_results = {{"calls", {"helper1", "helper2"}},
                            {"helper2", {"helper1"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Indirect calls statement") {
    std::string program =
        "procedure helper1 { call helper2; } procedure calls { call helper1; } "
        "procedure helper2 { print x; }";

    auto actual_results = InitializeCalls(program);

    std::unordered_map<std::string, std::unordered_set<std::string>>
        expected_results = {{"calls", {"helper1", "helper2"}},
                            {"helper1", {"helper2"}}};

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Calls statement within if and while") {
    std::string program =
        "procedure calls { while (x > 0) { print call; call helper1; } if (x "
        "== 0) then { x = x; } else { y = x; call helper2; } } procedure "
        "helper1 { print helper1; } procedure helper2 { read helper2; }";

    auto actual_results = InitializeCalls(program);

    std::unordered_map<std::string, std::unordered_set<std::string>>
        expected_results = {{"calls", {"helper1", "helper2"}}};

    REQUIRE(actual_results == expected_results);
  }
}
