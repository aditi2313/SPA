
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"

using std::string;
using std::vector;

std::unique_ptr<pkb::ModifiesTable> InitialiseModifiesTestTable(
    vector<std::unordered_set<string>> variables);

TEST_CASE("Test Modifies by variable Filter") {
  vector<std::unordered_set<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<std::unordered_set<string>> result_variables = {{"a", "b", "c"}, {"a", "b"}};
  auto table = InitialiseModifiesTestTable(variables);
  std::unordered_set < string > filtered = {"a"};
  filter::ModifiesPredicateFilter variable_filter(
      [filtered](pkb::ModifiesData data) {
        for (auto var : data.get_variables()) {
          if (filtered.find(var) != filtered.end()) {
            return true;
          }
        }
        return false;
      });
  auto new_table = variable_filter.FilterTable(std::move(table));
  auto expected = InitialiseModifiesTestTable(result_variables);
  REQUIRE(*expected == *new_table);
}

TEST_CASE("Test ModifiesFilterByLine") {
  vector<std::unordered_set<string>> variables = {
      {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

  vector<std::unordered_set<string>> result_variables = {{"a", "b", "c"}};
  auto table = InitialiseModifiesTestTable(variables);
  filter::ModifiesIndexFilter line_filter(0);

  auto new_table = line_filter.FilterTable(std::move(table));
  auto expected = InitialiseModifiesTestTable(result_variables);

  REQUIRE(*expected == *new_table);
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
