#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/FollowsVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

//pkb::FollowsTable InitializeActualResult(std::string program) {
//  std::unique_ptr<pkb::PKBRelationTable> table =
//      std::make_unique<pkb::PKBRelationTable>();
//  auto root = sp::SourceProcessor::ParseProgram(program);
//  sp::SourceProcessor::ExtractRelationships(root, table);
//  pkb::PKBRead reader(std::move(table));
//  auto ftr = std::make_unique<filter::FollowsPredicateFilter>(
//      [](pkb::FollowsData data) { return true; });
//  auto results_ptr = reader.Follows(std::move(ftr));
//  auto results = *(results_ptr->get_result());
//
//  return results;
//}

TEST_CASE("Test SP and PKB integration for FollowsT data") {
  // maybe move to FollowsTTest
  SECTION("Follows*(s1, s3) holds for three read statements") {
    std::string program = "procedure readfollows { read x; read y; read z; }";

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    std::unique_ptr<pkb::PKBRelationTable> actual_table =
        std::make_unique<pkb::PKBRelationTable>();

    auto root = sp::SourceProcessor::ParseProgram(program);
    sp::SourceProcessor::ExtractRelationships(root, actual_table);

    pkb::PKBWrite expected_writer(std::move(expected_table));
    expected_writer.AddFollowsData(1, 2);
    expected_writer.AddFollowsData(2, 3);
    expected_table = expected_writer.ProcessTableAndEndWrite();

    pkb::PKBRead expected_reader(std::move(expected_table));
    pkb::PKBRead actual_reader(std::move(actual_table));

    auto expected_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto expected_results = expected_reader.Follows(std::move(expected_ftr));
    auto actual_ftr = std::make_unique<filter::FollowsPredicateFilter>(
        [](pkb::FollowsData data) { return true; });
    auto actual_results = actual_reader.Follows(std::move(actual_ftr));

    REQUIRE(actual_results->get_result()->get_row(1).get_follows_list() ==
            expected_results->get_result()->get_row(1).get_follows_list());

    // REQUIRE(actual_results->get_result()->get_row(2).get_follows_list() ==
    //        expected_results->get_result()->get_row(2).get_follows_list());
  }

  SECTION("Follows") {}
}
