#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "PKB/data/UsesData.h"
#include "common/filter/filters/Export.h"

using std::string;
using std::vector;

std::unique_ptr<pkb::UsesTable> InitialiseUsesTestTable(
        vector<std::unordered_set<string>> variables);

TEST_CASE("Test Uses by variable Filter") {
    vector<std::unordered_set<string>> variables = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<std::unordered_set<string>> result_variables =
            {{"a", "b", "c"}, {"a", "b"}};
    auto table = InitialiseUsesTestTable(variables);
    std::unordered_set < string > filtered = {"a"};
    filter::UsesPredicateFilter variable_filter(
            [filtered](pkb::UsesData data) {
                for (auto var : data.get_variables()) {
                    if (filtered.find(var) != filtered.end()) {
                        return true;
                    }
                }
                return false;
            });
    auto& new_table = variable_filter.FilterTable(*table);
    auto expected = InitialiseUsesTestTable(result_variables);
    //REQUIRE(*expected == *new_table);
}

TEST_CASE("Test Uses by int line filter") {
    vector<std::unordered_set<string>> variables = {
            {"a", "b", "c"}, {"a", "b"}, {"k", "d", "m"}};

    vector<std::unordered_set<string>> result_variables = {{"a", "b", "c"}};
    auto table = InitialiseUsesTestTable(variables);
    filter::UsesIndexFilter line_filter(0);

    auto& new_table = line_filter.FilterTable(*table);
    auto expected = InitialiseUsesTestTable(result_variables);

    //REQUIRE(*expected == *new_table);
}

TEST_CASE("Test Uses by string line filter") {
    vector<std::unordered_set<string>> vars = {{"a", "c"}, {"a", "b"}};
    auto table = std::make_unique<pkb::UsesTable>();
    table->add_row("main", pkb::UsesData("main", vars.at(0)));
    table->add_row("helper", pkb::UsesData("helper", vars.at(1)));

    auto expected_table = std::make_unique<pkb::UsesTable>();
    expected_table->add_row("main", pkb::UsesData("main", vars.at(0)));

    filter::UsesIndexFilter line_filter("main");
    auto& actual_table = line_filter.FilterTable(*table);

    //REQUIRE(*actual_table == *expected_table);
}

std::unique_ptr<pkb::UsesTable> InitialiseUsesTestTable(
        vector<std::unordered_set<string>> variables) {
    std::unique_ptr<pkb::UsesTable> result = std::make_unique<pkb::UsesTable>();
    for (int i = 0; i < variables.size(); ++i) {
        result->add_row(i, pkb::UsesData(i, variables.at(i)));
    }
    return std::move(result);
}
