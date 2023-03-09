#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ParentVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::ParentTable InitializeParent(std::string program) {
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

pkb::ParentTable InitializeEmptyParent() {
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
    std::string program = "procedure parent { read x; }";

    auto actual_results = InitializeParent(program);

    auto expected_results = InitializeEmptyParent();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two read statements - empty table") {
    std::string program = "procedure parent { read x; read y; }";

    auto actual_results = InitializeParent(program);

    auto expected_results = InitializeEmptyParent();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship holds") {
    std::string program = "procedure parent { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeParent(program);

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

  SECTION("If statement - relationship holds for then and else stmtlsts") {
    std::string program =
        "procedure parent { if (x == 0) then { read x; } else { read y; } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(1, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested while loop - transitive relationship holds") {
    std::string program =
        "procedure parent { while (y > 5) { while (x < 3) { read z; } } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(2, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Triple nested while loop - transitive relationship holds") {
    std::string program =
        "procedure parent { while (x > 3) { while (x < 3) { while (x == 3) { "
        "read while; } } } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(2, 3);
    expected_writer.AddParentData(3, 4);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested if statement - transitive relationship holds") {
    std::string program =
        "procedure parent { if (x > 5) then { if (z > 5) then { read y; } else "
        "{ read x; } } else { if (y > 5) then { read x; } else { read y; } } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(1, 5);
    expected_writer.AddParentData(2, 3);
    expected_writer.AddParentData(2, 4);
    expected_writer.AddParentData(5, 6);
    expected_writer.AddParentData(5, 7);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two loops within a loop - relationship holds only in same branch") {
    std::string program =
        "procedure parent { while (y == 2) { if (x == 2) then { read x; } else "
        "{ read y; } while (x > 2) { read z; } } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(1, 5);
    expected_writer.AddParentData(2, 3);
    expected_writer.AddParentData(2, 4);
    expected_writer.AddParentData(5, 6);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Two if statements - relationship only holds for same branch and "
      "statement") {
    std::string program =
        "procedure parent { if (x == 0) then { read x; } else { read y; } if "
        "(y == x) then { read y; } else { read x; } }";

    auto actual_results = InitializeParent(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddParentData(1, 2);
    expected_writer.AddParentData(1, 3);
    expected_writer.AddParentData(4, 5);
    expected_writer.AddParentData(4, 6);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ParentPredicateFilter>(
        [](pkb::ParentData data) { return true; });
    auto expected_results_ptr = expected_reader.Parent(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }
}
