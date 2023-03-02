#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/FollowsVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::FollowsTable InitializeActualResult(std::string program) {
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

pkb::FollowsTable InitializeEmptyExpectedResult() {
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
  SECTION("There should be no data if there is only one statement") {
    std::string program = "procedure readfollows { read x; }";

    auto actual_results = InitializeActualResult(program);

    auto expected_results = InitializeEmptyExpectedResult();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Follows(s1, s2) holds for two read statements") {
    std::string program = "procedure readfollows { read x; read y; }";

    auto actual_results = InitializeActualResult(program);

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

  SECTION("Follows(s1, s2) holds for two assign statements") {
    std::string program = "procedure readfollows { x = 5; y = 3; }";
    auto actual_results = InitializeActualResult(program);

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

  SECTION("Follows(s1, s3) holds for two while loops") {
    std::string program =
        "procedure readfollows { while (i > 0) { i = i - 1; } while (j < 0) { "
        "j = j + 1; } }";
    auto actual_results = InitializeActualResult(program);

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

  SECTION("Follows(s1, s2) does not hold at different nesting levels") {
    std::string program =
        "procedure readfollows { while (x != 0) { y = y + 1; } }";

    auto actual_results = InitializeActualResult(program);

    auto expected_results = InitializeEmptyExpectedResult();

    REQUIRE(actual_results == expected_results);
  }

  SECTION(
      "Follows(s1, s2) holds at the same nesting level in an if statement") {
    std::string program =
        "procedure readfollows { if (x < 0) then { read x; read y; } else { "
        "read z; } "
        "}";
    auto actual_results = InitializeActualResult(program);

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

  SECTION("Follows(s1, s2) does not hold in different procedures") {
    std::string program =
        "procedure readfollows { x = 5; } procedure readfollows2 { y = 3; }";

    auto actual_results = InitializeActualResult(program);

    auto expected_results = InitializeEmptyExpectedResult();

    REQUIRE(actual_results == expected_results);
  }
}
