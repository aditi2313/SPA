#include <catch.hpp>
#include <unordered_set>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::ModifiesTable InitializeModifies(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ModifiesPredicateFilter>(
      [](pkb::ModifiesData data) { return true; });
  auto results_ptr = reader.Modifies(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

pkb::ModifiesTable InitializeEmptyModifies() {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ModifiesPredicateFilter>(
      [](pkb::ModifiesData data) { return true; });
  auto results_ptr = reader.Modifies(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

TEST_CASE("Test SP and PKB integration for Modifies data") {
  SECTION("Assign statement - 1 uses x") {
    std::string program = "procedure modifies { x = x; }";

    auto actual_results = InitializeModifies(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"x"});
    expected_writer.AddModifiesData(1, vars);
    expected_writer.AddModifiesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::ModifiesPredicateFilter>(
        [](pkb::ModifiesData data) { return true; });
    auto expected_results_ptr =
        expected_reader.Modifies(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }
}
