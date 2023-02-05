
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"
#include "common/filter/filters/ModifiesFilter.h"

using std::string;
using std::vector;

filter::ModifiesTablePtr InitialiseModifiesTestTable(
    vector<vector<string>> variables);

TEST_CASE("Test Modifies by variable Filter") {
  vector<vector<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<vector<string>> result_variables = {{"a", "b", "c"}, {"a", "b"}};
  auto table = InitialiseModifiesTestTable(variables);
  std::unordered_set < string > filtered = {"a"};
  filter::ModifiesFilterByVariable variable_filter(filtered);
  auto new_table = variable_filter.FilterTable(std::move(table));
  auto expected = InitialiseModifiesTestTable(result_variables);
  REQUIRE(*expected == *new_table);
}

TEST_CASE("Test ModifiesFilterByLine") {
  vector<vector<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<vector<string>> result_variables = {{"a", "b", "c"}};
  auto table = InitialiseModifiesTestTable(variables);
  filter::ModifiesFilterByLine line_filter(0);

  auto new_table = line_filter.FilterTable(std::move(table));
  auto expected = InitialiseModifiesTestTable(result_variables);

  REQUIRE(*expected == *new_table);
}

filter::ModifiesTablePtr InitialiseModifiesTestTable(
    vector<vector<string>> variables) {
  filter::ModifiesTablePtr result = std::make_unique<pkb::ModifiesTable>();
  for (int i = 0; i < variables.size(); ++i) {
    result->add_row(i, pkb::ModifiesData(i, variables.at(i)));
  }
  return std::move(result);
}
