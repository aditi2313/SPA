#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"
#include "Utility.h"
#include "common/filter/filters/Export.h"

using std::string;
using std::vector;

std::unique_ptr<pkb::ModifiesTable> InitialiseModifiesTestTable(
    vector<std::unordered_set<string>> variables);

std::vector<pkb::ModifiesData> InitialiseExpectedData(
    vector<std::unordered_set<string>> variables);

TEST_CASE("Test Modifies by variable Filter") {
  vector<std::unordered_set<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<std::unordered_set<string>> result_variables = {{"a", "b", "c"},
                                                         {"a", "b"}};
  auto table = InitialiseModifiesTestTable(variables);
  std::unordered_set<string> filtered = {"a"};
  filter::ModifiesPredicateFilter variable_filter(
      [filtered](pkb::ModifiesData data) {
        for (auto var : data.get_variables()) {
          if (filtered.find(var) != filtered.end()) {
            return true;
          }
        }
        return false;
      });
  auto& new_table = variable_filter.FilterTable(*table);
  auto expected = InitialiseExpectedData(result_variables);
  REQUIRE(CheckReaderEquality(expected, new_table));
}

TEST_CASE("Test int ModifiesFilterByLine") {
  vector<std::unordered_set<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<std::unordered_set<string>> result_variables = {{"a", "b", "c"}};
  auto table = InitialiseModifiesTestTable(variables);
  filter::ModifiesIndexFilter line_filter(0);

  auto& new_table = line_filter.FilterTable(*table);
  auto expected = InitialiseExpectedData(result_variables);

  REQUIRE(CheckReaderEquality(expected, new_table));
}

TEST_CASE("Test Modifies by string line filter") {
  vector<std::unordered_set<string>> vars = {{"a", "c"}, {"a", "b"}};
  auto table = std::make_unique<pkb::ModifiesTable>();
  table->add_row("main", pkb::ModifiesData("main", vars.at(0)));
  table->add_row("helper", pkb::ModifiesData("helper", vars.at(1)));

  std::vector<pkb::ModifiesData> expected_table;
  expected_table.push_back(pkb::ModifiesData("main", vars.at(0)));

  filter::ModifiesIndexFilter line_filter("main");
  auto& actual_table = line_filter.FilterTable(*table);

  REQUIRE(CheckReaderEquality(expected_table, actual_table));
}

std::unique_ptr<pkb::ModifiesTable> InitialiseModifiesTestTable(
    vector<std::unordered_set<string>> variables) {
  std::unique_ptr<pkb::ModifiesTable> result =
      std::make_unique<pkb::ModifiesTable>();
  for (int i = 0; i < variables.size(); ++i) {
    result->add_row(i, pkb::ModifiesData(i, variables.at(i)));
  }
  return std::move(result);
}

std::vector<pkb::ModifiesData> InitialiseExpectedData(
    vector<std::unordered_set<string>> variables) {
  std::vector<pkb::ModifiesData> result;
  for (int i = 0; i < variables.size(); ++i) {
    result.push_back(ModifiesData(i, variables.at(i)));
  }
  return result;
}
