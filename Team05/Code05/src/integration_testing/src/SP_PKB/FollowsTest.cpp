#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/FollowsVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::FollowsTable InitializeFollows(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::FollowsPredicateFilter>(
      [](pkb::FollowsData data) { return true; });
  auto results_ptr = reader.Follows(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

pkb::FollowsTable InitializeEmptyFollows() {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::FollowsPredicateFilter>(
      [](pkb::FollowsData data) { return true; });
  auto results_ptr = reader.Follows(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

TEST_CASE("Test SP and PKB integration for Follows data") {
  SECTION("One statement - empty table") {
    std::string program = "procedure follows { read x; }";

    auto actual_results = InitializeFollows(program);

    auto expected_results = InitializeEmptyFollows();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two read statements - relationship holds") {
    std::string program = "procedure follows { read x; read y; }";

    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(1, 2);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two assign statements - relationship holds") {
    std::string program = "procedure follows { x = 5; y = 3; }";
    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(1, 2);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two while loops - relationship does not hold for their stmtlsts") {
    std::string program =
        "procedure follows { while (i > 0) { i = i - 1; } while (j < 0) { "
        "j = j + 1; } }";
    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(1, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("While loop - relationship does not hold") {
    std::string program = "procedure follows { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeFollows(program);

    auto expected_results = InitializeEmptyFollows();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement - relationship only holds in same stmtlst") {
    std::string program =
        "procedure follows { if (x < 0) then { read x; read y; } else { "
        "read z; } "
        "}";
    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(2, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Two procedures - relationship does not hold") {
    std::string program =
        "procedure follows { x = 5; } procedure readfollows2 { y = 3; }";

    auto actual_results = InitializeFollows(program);

    auto expected_results = InitializeEmptyFollows();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Three read statements - transitive relationship holds") {
    std::string program = "procedure follows { read x; read y; read z; }";

    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();

    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(1, 2);
    expected_writer.AddFollowsData(2, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();

    pkb::PKBRead expected_reader(std::move(expected_table));

    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));

    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop - relationship only holds in same stmtlst") {
    std::string program =
        "procedure follows { while (x > 5) { print x; while (y > 3) { read y; "
        "print y; } } }";

    auto actual_results = InitializeFollows(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();

    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(2, 3);
    expected_writer.AddFollowsData(4, 5);
    expected_table = expected_writer.ProcessTableAndEndWrite();

    pkb::PKBRead expected_reader(std::move(expected_table));

    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Follows(std::move(expected_ftr));

    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }
}
