#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ParentVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::ParentTable InitializeActualResult(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ParentPredicateFilter>(
      [](pkb::ParentData data) { return true; });
  auto results_ptr = reader.Parent(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

pkb::ParentTable InitializeEmptyExpectedResult() {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ParentPredicateFilter>(
      [](pkb::ParentData data) { return true; });
  auto results_ptr = reader.Parent(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

TEST_CASE("Test SP and PKB integration for Parent Data") {
  SECTION("One statement - empty table") {
    std::string program = "procedure follows { read x; }";

    auto actual_results = InitializeActualResult(program);

    auto expected_results = InitializeEmptyExpectedResult();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two read statements - empty table") {
    std::string program = "procedure follows { read x; read y; }";

    auto actual_results = InitializeActualResult(program);

    auto expected_results = InitializeEmptyExpectedResult();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship holds") {
    std::string program = "procedure follows { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeActualResult(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }
}