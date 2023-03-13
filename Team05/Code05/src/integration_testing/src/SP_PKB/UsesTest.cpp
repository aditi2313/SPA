#include <catch.hpp>
#include <unordered_set>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/UsesVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::UsesTable InitializeUses(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::UsesPredicateFilter>(
      [](pkb::UsesData data) { return true; });
  auto results_ptr = reader.Uses(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

pkb::UsesTable InitializeEmptyUses() {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::UsesPredicateFilter>(
      [](pkb::UsesData data) { return true; });
  auto results_ptr = reader.Uses(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

TEST_CASE("Test SP and PKB integration for Uses data") {
  SECTION("Assign statement - 1 uses x") {
    std::string program = "procedure uses { x = x; }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"x"});
    expected_writer.AddUsesData(1, vars);
    //expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Assign statement - 1 uses y") {
    std::string program = "procedure uses { x = y; }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"y"});
    expected_writer.AddUsesData(1, vars);
    // expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Read statement - relationship does not hold") {
    std::string program = "procedure uses { read x; }";

    auto actual_results = InitializeUses(program);

    auto expected_results = InitializeEmptyUses();

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Print statement - relationship holds") {
    std::string program = "procedure uses { print x; }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"x"});
    expected_writer.AddUsesData(1, vars);
    // expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("If statement - relationship holds for cond") {
    std::string program =
        "procedure uses { if (((x == y) && (z > 3)) || (read < print)) then { read z; } else { print v; } }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"v", "x", "y", "z", "read", "print"});
    std::unordered_set<std::string> vars2({"v"});
    expected_writer.AddUsesData(1, vars);
    expected_writer.AddUsesData(3, vars2);
    //expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results == expected_results);
  }

  SECTION("Double nested loop - transitive condition holds") {
    std::string program =
        "procedure uses { while (x > y) { while (z == 3) { read v; } } }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"x", "y", "z"});
    std::unordered_set<std::string> vars2({"z"});
    expected_writer.AddUsesData(1, vars);
    expected_writer.AddUsesData(2, vars2);
    // expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results.get_row(2) == expected_results.get_row(2));  
  }

  SECTION("Calls statement") {
    std::string program =
        "procedure uses { print x; call helper; } procedure helper { while (z "
        "> 5) { print v; } }";

    auto actual_results = InitializeUses(program);

    std::unique_ptr<pkb::PKBRelationTable> expected_table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite expected_writer(std::move(expected_table));
    std::unordered_set<std::string> vars({"x"});
    std::unordered_set<std::string> vars2({"z", "v"});
    std::unordered_set<std::string> vars3({"v"});
    expected_writer.AddUsesData(1, vars);
    expected_writer.AddUsesData(2, vars2);
    expected_writer.AddUsesData(3, vars2);
    expected_writer.AddUsesData(4, vars3);
    // expected_writer.AddUsesData("uses", vars);
    expected_table = expected_writer.ProcessTableAndEndWrite();
    pkb::PKBRead expected_reader(std::move(expected_table));
    auto expected_ftr = std::make_unique<filter::UsesPredicateFilter>(
        [](pkb::UsesData data) { return true; });
    auto expected_results_ptr = expected_reader.Uses(std::move(expected_ftr));
    auto expected_results = *(expected_results_ptr->get_result());

    REQUIRE(actual_results.get_row(4) == expected_results.get_row(4)); 
  }
}
