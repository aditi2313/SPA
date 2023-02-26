#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/UsesVisitor.h"

TEST_CASE("Test SP and PKB integration for Uses data") {
  SECTION("") {
    std::string program = "";
    std::unique_ptr<pkb::PKBRelationTable> expected_results =
        std::make_unique<pkb::PKBRelationTable>();
    std::unique_ptr<pkb::PKBRelationTable> actual_results =
        std::make_unique<pkb::PKBRelationTable>();
    auto root = sp::SourceProcessor::ParseProgram(program);
    sp::SourceProcessor::ExtractRelationships(root, actual_results);

    REQUIRE(actual_results == expected_results);
  }
}